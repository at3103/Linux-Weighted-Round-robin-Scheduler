#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	struct sched_param param;
	param.sched_priority = 0;
	printf(
		"Setting sched: %d\n%s\n",
		sched_setscheduler(0, 6, &param),
		strerror(errno)
	);
	int i = 1;
	while (1) {
		fork();
		printf("Scheduler: %d\n", sched_getscheduler(0));
		if (i == 10) {
			printf("ab");
			exit(0);
		}
		i++;
	}
}
