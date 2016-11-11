/*
 * Weighted Round Robin Scheduling Class (mapped to the SCHED_WRR policy)
 */

#include "sched.h"

int wrr_weight = MAX_WRR_WEIGHT;

void set_wrr_weight(int weight)
{
	wrr_weight = weight;
}
static int pull_task_from_cpus(struct rq *cur_rq);

void init_wrr_rq(struct wrr_rq *wrr_rq, struct rq *rq)
{
	INIT_LIST_HEAD(&wrr_rq->queue);
}

static int should_boost(struct task_struct *p)
{
	return (p->cred->uid >= 10000);
}

static void
enqueue_task_wrr_internal(struct rq *rq, struct task_struct *p, int flags,
	int weight)
{
	p->wrr.weight = weight;
	rq->wrr.total_weight += weight;
	p->wrr.time_slice = WRR_TIMESLICE * weight;
	INIT_LIST_HEAD(&p->wrr.run_list);
	list_add_tail(&p->wrr.run_list, &rq->wrr.queue);
	inc_nr_running(rq);
	rq->wrr.nr_running++;
}

static void dequeue_task_wrr(struct rq *rq, struct task_struct *p, int flags)
{
	list_del(&(p->wrr.run_list));
	dec_nr_running(rq);
	rq->wrr.nr_running--;
	rq->wrr.total_weight -= p->wrr.weight;
	if (p->wrr.weight > 1)
		p->wrr.weight = p->wrr.weight - 1;

	#ifdef CONFIG_SMP
	if (rq->wrr.nr_running == 0)
		pull_task_from_cpus(rq);
	#endif /*CONFIG_SMP*/
}

static void timeslice_end(struct rq *rq, struct task_struct *p, int queued)
{
	dequeue_task_wrr(rq, p, 0);
	p->wrr.time_slice = WRR_TIMESLICE * p->wrr.weight;
	enqueue_task_wrr_internal(rq, p, 0, p->wrr.weight);
	set_tsk_need_resched(p);
}

static void
enqueue_task_wrr(struct rq *rq, struct task_struct *p, int flags)
{
	if (!p->wrr.was_boosted || p->wrr.weight <= 0 ||
		p->wrr.weight > wrr_weight) {
		if (should_boost(p))
			p->wrr.weight = wrr_weight;
		else
			p->wrr.weight = 1;
		p->wrr.was_boosted = 1;
	}
	enqueue_task_wrr_internal(rq, p, flags, p->wrr.weight);
}

static int
select_task_rq_wrr(struct task_struct *p, int sd_flags, int wake_flags)
{
	int cur_cpu = task_cpu(p), cpu, new_cpu;
	struct rq *rq = cpu_rq(cur_cpu), *tmp_rq;
	int low_weight = rq->wrr.total_weight;

	new_cpu = cur_cpu;

	if (p->nr_cpus_allowed == 1)
		return cur_cpu;

	rcu_read_lock();
	for_each_possible_cpu(cpu) {
		tmp_rq = cpu_rq(cpu);
		if (tmp_rq->wrr.total_weight < low_weight) {
			low_weight = tmp_rq->wrr.total_weight;
			new_cpu = cpu;
		}

	}

	rcu_read_unlock();

	return new_cpu;
}

static struct task_struct *_find_container(struct list_head *cursor)
{
	return container_of(list_entry(cursor, struct sched_wrr_entity,
					run_list),
			struct task_struct, wrr);
}

static void yield_task_wrr(struct rq *rq)
{
	struct task_struct *curr = rq->curr;
	dequeue_task_wrr(rq, curr, 0);
	enqueue_task_wrr(rq, curr, 0);
}

static bool yield_to_task_wrr(
	struct rq *rq,
	struct task_struct *p,
	bool preempt
)
{
	return 0;
}

static void check_preempt_curr_wrr(
	struct rq *rq,
	struct task_struct *p,
	int flags
)
{
}

static struct task_struct *pick_next_task_wrr(struct rq *rq)
{
	struct task_struct *next = NULL;
	if (!list_empty(&(rq->wrr.queue)))
		next = _find_container(rq->wrr.queue.next);
	return next;
}

static void put_prev_task_wrr(struct rq *rq, struct task_struct *p)
{
}

static void set_curr_task_wrr(struct rq *rq)
{
}

static void task_tick_wrr(struct rq *rq, struct task_struct *p, int queued)
{
	if (--p->wrr.time_slice)
		return;
	timeslice_end(rq, p, queued);
}

static void task_fork_wrr(struct task_struct *p)
{
	p->wrr.was_boosted = 0;
}

static void switched_from_wrr(struct rq *this_rq, struct task_struct *task)
{

}

static void switched_to_wrr(struct rq *this_rq, struct task_struct *task)
{

}

static void prio_changed_wrr(
	struct rq *this_rq,
	struct task_struct *task,
	int oldprio
)
{

}

static unsigned int get_rr_interval_wrr(struct rq *rq, struct task_struct *task)
{
	return 0;
}

static int pull_task_from_cpus(struct rq *cur_rq)
{
	int cur_cpu = cur_rq->cpu, ret = 0, cpu;
	struct rq *src_rq;
	struct task_struct *p;

	if (cur_rq->wrr.nr_running > 0)
		return ret;

	for_each_cpu(cpu, cur_rq->rd->rto_mask) {

		if (cpu == cur_cpu)
			continue;

		src_rq = cpu_rq(cpu);

		double_lock_balance(cur_rq, src_rq);

		if (src_rq->wrr.nr_running < 2) {
			double_unlock_balance(cur_rq, src_rq);
			continue;
		}

		if (cur_rq->wrr.nr_running > 0) {
			double_unlock_balance(cur_rq, src_rq);
			break;
		}


		/*Gets the next task from the run queue
		*of the presently iterating cpu
		*/
		p = pick_next_task_wrr(src_rq);
		if (p) {
			WARN_ON(p == src_rq->curr);
			WARN_ON(!p->on_rq);

			if (p->nr_cpus_allowed == 1) {
				double_unlock_balance(cur_rq, src_rq);
				continue;
			}
			ret = 1;

			/*Deactivates, dequeues from the old cpu
			*and enqueues to the new cpu
			*/
			deactivate_task(src_rq, p, 0);
			set_task_cpu(p, cur_cpu);
			activate_task(cur_rq, p, 0);
			double_unlock_balance(cur_rq, src_rq);
			break;
		}
		double_unlock_balance(cur_rq, src_rq);
	}

	return ret;
}


const struct sched_class sched_wrr_class = {
	.next                   = &fair_sched_class,
	.enqueue_task           = enqueue_task_wrr,
	.dequeue_task           = dequeue_task_wrr,
	.yield_task             = yield_task_wrr,
	.yield_to_task          = yield_to_task_wrr,
	.check_preempt_curr     = check_preempt_curr_wrr,
#ifdef CONFIG_SMP
	.select_task_rq			= select_task_rq_wrr,
#endif
	.pick_next_task         = pick_next_task_wrr,
	.put_prev_task          = put_prev_task_wrr,
	.set_curr_task          = set_curr_task_wrr,
	.task_tick              = task_tick_wrr,
	.task_fork              = task_fork_wrr,
	.prio_changed           = prio_changed_wrr,
	.switched_from          = switched_from_wrr,
	.switched_to            = switched_to_wrr,
	.get_rr_interval        = get_rr_interval_wrr,
};
