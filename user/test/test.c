#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char **argv)
{
	struct wrr_info info;
	int j = 0;

	if (argc == 1) {
		while(1) {
			syscall(244, &info);
			for(j = 0; j < info.num_cpus; j++)
				printf("CPU %d has %d processes with total weight %d\n",
				       j, (int)info.nr_running[j], (int)info.total_weight[j]);
			sleep(1);
		}
	} else {
		j = atoi(argv[1]);
		syscall(245, j);
	}
	return 0;
}
