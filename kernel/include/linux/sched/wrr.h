#ifndef _SCHED_WRR_H
#define _SCHED_WRR_H

#define WRR_TIMESLICE 10
#define MAX_WRR_WEIGHT 10
#define MAX_CPUS 8

struct wrr_info {
	int num_cpus;
	int nr_running[MAX_CPUS];
	int total_weight[MAX_CPUS];
};

#endif
