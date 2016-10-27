/*
 * Weighted Round Robin Scheduling Class (mapped to the SCHED_WRR policy)
 */

#include "sched.h"

void init_wrr_rq(struct wrr_rq *wrr_rq, struct rq *rq)
{
	struct wrr_queues *array;
	int i;

	array = &wrr_rq->wrr_q;
	for (i = 0; i < MAX_WRR_WEIGHT; i++)
		INIT_LIST_HEAD(array->queues + i);
}

int alloc_wrr_sched_group(struct task_group *tg, struct task_group *parent)
{
	return 1;
}

static void enqueue_task_wrr(struct rq *rq, struct task_struct *p, int flags)
{

}

static void dequeue_task_wrr(struct rq *rq, struct task_struct *p, int flags)
{

}

static void yield_task_wrr(struct rq *rq)
{

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
	return NULL;
}

static void put_prev_task_wrr(struct rq *rq, struct task_struct *p)
{

}

static void set_curr_task_wrr(struct rq *rq)
{

}

static void task_tick_wrr(struct rq *rq, struct task_struct *p, int queued)
{

}

static void task_fork_wrr(struct task_struct *p)
{

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
