/*
 * Weighted Round Robin Scheduling Class (mapped to the SCHED_WRR policy)
 */

#include "sched.h"
#include <linux/printk.h>

int wrr_weight = MAX_WRR_WEIGHT - 1;

void set_wrr_weight(int weight)
{
	wrr_weight = weight - 1;
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
	printk(KERN_DEFAULT "Enqueued task i");
	struct list_head wrr_q;

	p->wrr.weight = weight;
	p->wrr.time_slice = WRR_TIMESLICE * (weight + 1) * 10;
	INIT_LIST_HEAD(&p->wrr.run_list);
	list_add_tail(&p->wrr.run_list, &rq->wrr.queue);
	inc_nr_running(rq);
}

static void dequeue_task_wrr(struct rq *rq, struct task_struct *p, int flags)
{
	printk(KERN_DEFAULT "Dequeued task");
	list_del(&(p->wrr.run_list));
	dec_nr_running(rq);

	/*May be check if it is multi_core or something*/
	#ifdef CONFIG_SMP
	if (rq->nr_running == 0)
		if (pull_task_from_cpus(rq))
			;/*Handle error*/
	#endif /*CONFIG_SMP*/
}

static void timeslice_end(struct rq *rq, struct task_struct *p, int queued)
{
	dequeue_task_wrr(rq, p, 0);
	if (p->wrr.weight > 0)
		--p->wrr.weight;
	p->wrr.time_slice = WRR_TIMESLICE * (p->wrr.weight + 1) * 10;
	enqueue_task_wrr_internal(rq, p, 0, p->wrr.weight);
	set_tsk_need_resched(p);
}

static void
enqueue_task_wrr(struct rq *rq, struct task_struct *p, int flags)
{
	printk(KERN_DEFAULT "\nEnqueued task %d", (int)p->pid);
	int weight = wrr_weight;

	if (!should_boost(p)) {
		weight = 0;
	}
	enqueue_task_wrr_internal(rq, p, weight, flags);
}


struct task_struct *_find_container(struct list_head *cursor)
{
	return container_of(list_entry(cursor, struct sched_wrr_entity,
					run_list),
			struct task_struct, wrr);
}

static void yield_task_wrr(struct rq *rq)
{
	printk(KERN_DEFAULT "Yield task");
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
	printk(KERN_DEFAULT "Yield to task");
	return 0;
}

static void check_preempt_curr_wrr(
	struct rq *rq,
	struct task_struct *p,
	int flags
)
{
	//resched_task(rq->curr);
}

static struct task_struct *pick_next_task_wrr(struct rq *rq)
{
	struct task_struct *next = NULL;
	int i;
	printk(KERN_DEFAULT "Pick task");
	if (!list_empty(&(rq->wrr.queue)))
		next = _find_container(rq->wrr.queue.next);
	return next;
}

static void put_prev_task_wrr(struct rq *rq, struct task_struct *p)
{
	printk(KERN_DEFAULT "Put task");

}

static void set_curr_task_wrr(struct rq *rq)
{
	printk(KERN_DEFAULT "Set task");

}

static void task_tick_wrr(struct rq *rq, struct task_struct *p, int queued)
{
	printk(KERN_DEFAULT "Tick task");
	if (--p->wrr.time_slice)
		return;
	timeslice_end(rq, p, queued);
}

static void task_fork_wrr(struct task_struct *p)
{
	printk(KERN_DEFAULT "Fork task");

}

static void switched_from_wrr(struct rq *this_rq, struct task_struct *task)
{
	printk(KERN_DEFAULT "Switch from task");

}

static void switched_to_wrr(struct rq *this_rq, struct task_struct *task)
{
	printk(KERN_DEFAULT "Switch to task");

}

static void prio_changed_wrr(
	struct rq *this_rq,
	struct task_struct *task,
	int oldprio
)
{
	printk(KERN_DEFAULT "Prio task");

}

static unsigned int get_rr_interval_wrr(struct rq *rq, struct task_struct *task)
{
	printk(KERN_DEFAULT "Interval task");
	return 0;
}

static int pull_task_from_cpus(struct rq *cur_rq)
{
	int cur_cpu = cur_rq->cpu, ret = 0, cpu;
	struct rq *src_rq;
	struct task_struct *p;

	if (cur_rq->nr_running > 0)
		return ret;

	for_each_cpu(cpu, cur_rq->rd->rto_mask) {

		if (cpu == cur_cpu)
			continue;

		src_rq = cur_rq;

		double_lock_balance(cur_rq, src_rq);

		if (src_rq->nr_running < 2) {
			double_unlock_balance(cur_rq, src_rq);
			continue;
		}

		if (cur_rq->nr_running > 0) {
			double_unlock_balance(cur_rq, src_rq);
			break;
		}

		/*Gets the next task from the run queue
		*of the presently iterating cpu
		*/
		p = pick_next_task_wrr(src_rq);
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

	return ret;
}


const struct sched_class sched_wrr_class = {
	.next                   = &fair_sched_class,
	.enqueue_task           = enqueue_task_wrr,
	.dequeue_task           = dequeue_task_wrr,
	.yield_task             = yield_task_wrr,
	.yield_to_task          = yield_to_task_wrr,
	.check_preempt_curr     = check_preempt_curr_wrr,
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
