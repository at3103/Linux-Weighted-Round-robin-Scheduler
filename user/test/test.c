#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CPUS 8
struct wrr_info {
        int num_cpus;
        int nr_running[MAX_CPUS];
        int total_weight[MAX_CPUS];
};

int main(void)
{
	struct sched_param param;
	param.sched_priority = 0;
	int j = 0;
	struct wrr_info info;
	syscall(244, &info);
	for(j = 0; j < info.num_cpus; j++) {
		printf("CPU %d has %d processes with total weight %d\n", j, (int)info.nr_running[j], (int)info.total_weight[j]);
	}
	sleep(10);
	printf(
		"Setting sched: %d\n%s\n",
		sched_setscheduler(0, 6, &param),
		strerror(errno)
	);
	syscall(244, &info);
	for(j = 0; j < info.num_cpus; j++) {
		printf("CPU %d has %d processes with total weight %d\n", j, (int)info.nr_running[j], (int)info.total_weight[j]);
	}
	return 0;
}
