## Upload and Run Test Program
First of all, test program is uploaded using `adb push` (make sure phone is plugged in):
```
> adb push build-master/test/test /data/misc/test
```
After that, `ssh` on to the phone and run it:
```
> adb shell
(in phone)> /data/misc/test <optional positive number>
```
Note the difference of whether to provide optional positive number or not: the positive number, if provided, would change the maximum weight of each task applying wrr scheduling policy to be equal to it; If no argument is provided, the test program will continuously print out the workload allocation accross different CPUs, with 1 sec's time interval.

Also note that only root users will have the previledge of setting up wrr weight.

## Recommended Test Scenarios
### Basic test
Since the weighted round robin scheduler is applied by `init` process and set to be the default scheduler for apps. It is expected that the majority of apps are using the scheduler.

##### Steps of Test
* Reboot the phone with custom kernel;
* At an early stage of booting (for example, immediately after phone is accessible via USB), run test program to see real-time wrr workload allocations. Reason: a large number of apps will be initialized during bootup and then set to sleep. So a significant rise of wrr workload is expected at the same time.

##### Expected Results
```
CPU 1 has 0 processes with total weight 0
CPU 2 has 0 processes with total weight 0
CPU 3 has 0 processes with total weight 0
CPU 4 has 22 processes with total weight 22
CPU 5 has 0 processes with total weight 0
CPU 6 has 0 processes with total weight 0
CPU 7 has 0 processes with total weight 0

CPU 0 has 5 processes with total weight 5
CPU 1 has 4 processes with total weight 4
CPU 2 has 4 processes with total weight 4
CPU 3 has 3 processes with total weight 3
CPU 4 has 2 processes with total weight 2
CPU 5 has 3 processes with total weight 3
CPU 6 has 4 processes with total weight 4
CPU 7 has 3 processes with total weight 3

CPU 0 has 5 processes with total weight 5
CPU 1 has 4 processes with total weight 4
CPU 2 has 4 processes with total weight 4
CPU 3 has 3 processes with total weight 3
CPU 4 has 3 processes with total weight 3
CPU 5 has 3 processes with total weight 3
CPU 6 has 4 processes with total weight 4
CPU 7 has 3 processes with total weight 3

CPU 0 has 5 processes with total weight 5
CPU 1 has 4 processes with total weight 4
CPU 2 has 4 processes with total weight 4
CPU 3 has 3 processes with total weight 3
CPU 4 has 3 processes with total weight 3
CPU 5 has 2 processes with total weight 2
CPU 6 has 4 processes with total weight 4
CPU 7 has 3 processes with total weight 3

CPU 0 has 5 processes with total weight 5
CPU 1 has 4 processes with total weight 4
CPU 2 has 4 processes with total weight 4
CPU 3 has 3 processes with total weight 3
CPU 4 has 3 processes with total weight 3
CPU 5 has 2 processes with total weight 2
CPU 6 has 4 processes with total weight 4
CPU 7 has 3 processes with total weight 3

CPU 0 has 5 processes with total weight 5
CPU 1 has 4 processes with total weight 4
CPU 2 has 4 processes with total weight 4
CPU 3 has 4 processes with total weight 4
CPU 4 has 4 processes with total weight 4
CPU 5 has 4 processes with total weight 4
CPU 6 has 3 processes with total weight 3
CPU 7 has 3 processes with total weight 3

CPU 0 has 5 processes with total weight 5
CPU 1 has 4 processes with total weight 4
CPU 2 has 4 processes with total weight 4
CPU 3 has 4 processes with total weight 4
CPU 4 has 4 processes with total weight 4
CPU 5 has 4 processes with total weight 4
CPU 6 has 4 processes with total weight 4
CPU 7 has 3 processes with total weight 3

*CPU 7 has the least total weight --> Hence, new process gets assigned to it.

CPU 0 has 5 processes with total weight 5
CPU 1 has 4 processes with total weight 4
CPU 2 has 4 processes with total weight 4
CPU 3 has 4 processes with total weight 4
CPU 4 has 4 processes with total weight 4
CPU 5 has 4 processes with total weight 4
CPU 6 has 4 processes with total weight 4
CPU 7 has 4 processes with total weight 4

CPU 0 has 5 processes with total weight 5
CPU 1 has 4 processes with total weight 4
CPU 2 has 4 processes with total weight 4
CPU 3 has 4 processes with total weight 4
CPU 4 has 4 processes with total weight 4
CPU 5 has 5 processes with total weight 5
CPU 6 has 4 processes with total weight 4
CPU 7 has 4 processes with total weight 4

CPU 0 has 5 processes with total weight 5
CPU 1 has 4 processes with total weight 4
CPU 2 has 4 processes with total weight 4
CPU 3 has 4 processes with total weight 4
CPU 4 has 5 processes with total weight 5
CPU 5 has 5 processes with total weight 5
CPU 6 has 4 processes with total weight 4
CPU 7 has 4 processes with total weight 4

*Boosted process with weight 10 at CPU 5
*Once, all it's five processes finishes, it will have zero processes, hence new process gets added to its queue.
CPU 0 has 4 processes with total weight 4
CPU 1 has 4 processes with total weight 4
CPU 2 has 3 processes with total weight 5
CPU 3 has 4 processes with total weight 4
CPU 4 has 2 processes with total weight 9
CPU 5 has 1 processes with total weight 9
CPU 6 has 3 processes with total weight 3
CPU 7 has 3 processes with total weight 3


CPU 0 has 4 processes with total weight 4
CPU 1 has 4 processes with total weight 12
CPU 2 has 3 processes with total weight 3
CPU 3 has 5 processes with total weight 5
CPU 4 has 4 processes with total weight 4
CPU 5 has 2 processes with total weight 2
CPU 6 has 2 processes with total weight 2
CPU 7 has 2 processes with total weight 2

CPU 0 has 2 processes with total weight 2
CPU 1 has 3 processes with total weight 3
CPU 2 has 1 processes with total weight 2
CPU 3 has 2 processes with total weight 2
CPU 4 has 2 processes with total weight 2
CPU 5 has 2 processes with total weight 2
CPU 6 has 1 processes with total weight 84
CPU 7 has 1 processes with total weight 1

CPU 0 has 1 processes with total weight 1
CPU 1 has 1 processes with total weight 47
CPU 2 has 1 processes with total weight 87
CPU 3 has 1 processes with total weight 34
CPU 4 has 1 processes with total weight 1
CPU 5 has 1 processes with total weight 91
CPU 6 has 4 processes with total weight 4
CPU 7 has 1 processes with total weight 49

CPU 0 has 2 processes with total weight 2
CPU 1 has 1 processes with total weight 1
CPU 2 has 0 processes with total weight 0
CPU 3 has 1 processes with total weight 1
CPU 4 has 1 processes with total weight 1
CPU 5 has 1 processes with total weight 1
CPU 6 has 1 processes with total weight 1
CPU 7 has 0 processes with total weight 0

CPU 0 has 3 processes with total weight 97
CPU 1 has 1 processes with total weight 1
CPU 2 has 1 processes with total weight 1
CPU 3 has 1 processes with total weight 1
CPU 4 has 1 processes with total weight 1
CPU 5 has 0 processes with total weight 0
CPU 6 has 0 processes with total weight 0
CPU 7 has 0 processes with total weight 0

```
### Test on different weights
The weight controls the frequency of reschedule. Generally speaking, larger weight discourages multi-process while smaller weight magnifies reschedule overhead.

##### Steps of Test
* Use test program to set weight to 1, then simply play around with the phone;
* Use test program to set weight to 1000, then try multi-process by opening up google play store while browser is loading a page.

##### Expected Results
```
CPU 0 has 9 processes with total weight 256
CPU 1 has 0 processes with total weight 0
CPU 2 has 0 processes with total weight 0
CPU 3 has 0 processes with total weight 0
CPU 4 has 0 processes with total weight 0
CPU 5 has 0 processes with total weight 0
CPU 6 has 0 processes with total weight 0
CPU 7 has 0 processes with total weight 0

CPU 0 has 1 processes with total weight 1
CPU 1 has 3 processes with total weight 3
CPU 2 has 3 processes with total weight 3
CPU 3 has 1 processes with total weight 1
CPU 4 has 3 processes with total weight 3
CPU 5 has 1 processes with total weight 1
CPU 6 has 1 processes with total weight 217
CPU 7 has 1 processes with total weight 1
CPU 0 has 1 processes with total weight 135
CPU 7 has 3 processes with total weight 3

CPU 0 has 1 processes with total weight 1
CPU 1 has 2 processes with total weight 171
CPU 2 has 3 processes with total weight 197
CPU 3 has 2 processes with total weight 2
CPU 4 has 4 processes with total weight 4
CPU 5 has 2 processes with total weight 2
CPU 6 has 1 processes with total weight 1
CPU 7 has 3 processes with total weight 3

CPU 0 has 1 processes with total weight 100
CPU 1 has 2 processes with total weight 171
CPU 2 has 3 processes with total weight 197
CPU 3 has 3 processes with total weight 202
CPU 4 has 4 processes with total weight 4
CPU 5 has 2 processes with total weight 2
CPU 6 has 2 processes with total weight 2
CPU 7 has 3 processes with total weight 3

CPU 0 has 1 processes with total weight 100
CPU 1 has 2 processes with total weight 171
CPU 2 has 3 processes with total weight 197
CPU 3 has 3 processes with total weight 202
CPU 4 has 4 processes with total weight 4
CPU 5 has 2 processes with total weight 2
CPU 6 has 0 processes with total weight 0
CPU 7 has 3 processes with total weight 3


root@HNKIW-Q:/data/misc # ./test 200                                           
Changed weight to 200

CPU 0 has 2 processes with total weight 2
CPU 1 has 1 processes with total weight 200
CPU 2 has 1 processes with total weight 1
CPU 3 has 0 processes with total weight 0
CPU 4 has 0 processes with total weight 0
CPU 5 has 0 processes with total weight 0
CPU 6 has 0 processes with total weight 0
CPU 7 has 0 processes with total weight 0

CPU 0 has 2 processes with total weight 2
CPU 1 has 1 processes with total weight 196
CPU 2 has 1 processes with total weight 1
CPU 3 has 1 processes with total weight 200
CPU 4 has 0 processes with total weight 0
CPU 5 has 0 processes with total weight 0
CPU 6 has 0 processes with total weight 0
CPU 7 has 0 processes with total weight 0

CPU 0 has 2 processes with total weight 2
CPU 1 has 1 processes with total weight 195
CPU 2 has 1 processes with total weight 1
CPU 3 has 1 processes with total weight 198
CPU 4 has 0 processes with total weight 0
CPU 5 has 0 processes with total weight 0
CPU 6 has 1 processes with total weight 1
CPU 7 has 0 processes with total weight 0

root@HNKIW-Q:/data/misc # ./test 100                                           
Changed weight to 100

CPU 0 has 1 processes with total weight 1
CPU 1 has 0 processes with total weight 0
CPU 2 has 0 processes with total weight 0
CPU 3 has 1 processes with total weight 1
CPU 4 has 0 processes with total weight 0
CPU 5 has 1 processes with total weight 1
CPU 6 has 0 processes with total weight 0
CPU 7 has 1 processes with total weight 88

CPU 0 has 1 processes with total weight 1
CPU 1 has 0 processes with total weight 0
CPU 2 has 1 processes with total weight 1
CPU 3 has 1 processes with total weight 71
CPU 4 has 1 processes with total weight 1
CPU 5 has 0 processes with total weight 0
CPU 6 has 0 processes with total weight 0
CPU 7 has 1 processes with total weight 1
CPU 0 has 0 processes with total weight 0

root@HNKIW-Q:/data/misc # ./test 100                                           
Changed weight to 100

CPU 0 has 9 processes with total weight 107
CPU 1 has 0 processes with total weight 0
CPU 2 has 0 processes with total weight 0
CPU 3 has 0 processes with total weight 0
CPU 4 has 0 processes with total weight 0
CPU 5 has 0 processes with total weight 0
CPU 6 has 0 processes with total weight 0
CPU 7 has 0 processes with total weight 0



```
### Test load balancing
The load balancing mechanism is expected to allocate workload evenly across multiple cores, even under scenarios where non-trivial number of processes are spawned.

##### Steps of Test
* Run test program to keep monitoring wrr workload allocation.
* Spawn multiple processes in the test program. We can see the load getting balanced between the cpus.

##### Expected Results
```
root@HNKIW-Q:/data/misc # ./test
CPU 0 has 1 processes with total weight 1
CPU 1 has 1 processes with total weight 1
CPU 2 has 1 processes with total weight 1
CPU 3 has 0 processes with total weight 0
CPU 4 has 0 processes with total weight 0
CPU 5 has 2 processes with total weight 2
CPU 6 has 0 processes with total weight 0
CPU 7 has 0 processes with total weight 0

*Example where the new processes get alloted evenly

CPU 0 has 3 processes with total weight 3
CPU 1 has 3 processes with total weight 3
CPU 2 has 1 processes with total weight 1
CPU 3 has 3 processes with total weight 3
CPU 4 has 2 processes with total weight 2
CPU 5 has 2 processes with total weight 2
CPU 6 has 2 processes with total weight 2
CPU 7 has 3 processes with total weight 3

CPU 0 has 2 processes with total weight 2
CPU 1 has 2 processes with total weight 2
CPU 2 has 2 processes with total weight 2
CPU 3 has 2 processes with total weight 2
CPU 4 has 2 processes with total weight 2
CPU 5 has 1 processes with total weight 1
CPU 6 has 1 processes with total weight 1
CPU 7 has 5 processes with total weight 5

CPU 0 has 5 processes with total weight 5
CPU 1 has 1 processes with total weight 1
CPU 2 has 1 processes with total weight 1
CPU 3 has 2 processes with total weight 2
CPU 4 has 3 processes with total weight 3
CPU 5 has 2 processes with total weight 2
CPU 6 has 5 processes with total weight 5
CPU 7 has 2 processes with total weight 2

*Load balancing at work

CPU 0 has 3 processes with total weight 3
CPU 1 has 2 processes with total weight 2
CPU 2 has 3 processes with total weight 3
CPU 3 has 4 processes with total weight 4
CPU 4 has 3 processes with total weight 3
CPU 5 has 3 processes with total weight 3
CPU 6 has 3 processes with total weight 3
CPU 7 has 3 processes with total weight 3

CPU 0 has 4 processes with total weight 4
CPU 1 has 2 processes with total weight 2
CPU 2 has 4 processes with total weight 4
CPU 3 has 4 processes with total weight 4
CPU 4 has 4 processes with total weight 4
CPU 5 has 4 processes with total weight 4
CPU 6 has 0 processes with total weight 0
CPU 7 has 4 processes with total weight 4

CPU 0 has 5 processes with total weight 11
CPU 1 has 11 processes with total weight 11
CPU 2 has 3 processes with total weight 3
CPU 3 has 3 processes with total weight 3
CPU 4 has 10 processes with total weight 10
CPU 5 has 3 processes with total weight 3
CPU 6 has 2 processes with total weight 2
CPU 7 has 1 processes with total weight 1

CPU 0 has 2 processes with total weight 2
CPU 1 has 2 processes with total weight 2
CPU 2 has 2 processes with total weight 2
CPU 3 has 2 processes with total weight 2
CPU 4 has 2 processes with total weight 2
CPU 5 has 1 processes with total weight 1
CPU 6 has 1 processes with total weight 1
CPU 7 has 1 processes with total weight 1
CPU 0 has 1 processes with total weight 1
CPU 1 has 1 processes with total weight 1
CPU 2 has 2 processes with total weight 2
CPU 3 has 1 processes with total weight 1
CPU 4 has 1 processes with total weight 1
CPU 5 has 1 processes with total weight 1
CPU 6 has 0 processes with total weight 0
CPU 7 has 2 processes with total weight 2

CPU 0 has 2 processes with total weight 2
CPU 1 has 1 processes with total weight 1
CPU 2 has 55 processes with total weight 55
CPU 3 has 1 processes with total weight 1
CPU 4 has 24 processes with total weight 24
CPU 5 has 1 processes with total weight 1
CPU 6 has 1 processes with total weight 1
CPU 7 has 24 processes with total weight 24

CPU 0 has 3 processes with total weight 3
CPU 1 has 0 processes with total weight 0
CPU 2 has 2 processes with total weight 2
CPU 3 has 1 processes with total weight 1
CPU 4 has 18 processes with total weight 18
CPU 5 has 90 processes with total weight 90
CPU 6 has 90 processes with total weight 90
CPU 7 has 0 processes with total weight 0

CPU 0 has 133 processes with total weight 133
CPU 1 has 1 processes with total weight 1
CPU 3 has 131 processes with total weight 131
CPU 4 has 48 processes with total weight 48
CPU 5 has 5 processes with total weight 5
CPU 6 has 22 processes with total weight 22
CPU 7 has 132 processes with total weight 132

CPU 0 has 213 processes with total weight 213
CPU 1 has 213 processes with total weight 213
CPU 2 has 213 processes with total weight 213
CPU 3 has 213 processes with total weight 213
CPU 4 has 89 processes with total weight 89
CPU 5 has 213 processes with total weight 213
CPU 6 has 1 processes with total weight 1
CPU 7 has 135 processes with total weight 135

CPU 0 has 108 processes with total weight 108
CPU 1 has 1 processes with total weight 1
CPU 2 has 2 processes with total weight 2
CPU 3 has 108 processes with total weight 108
CPU 4 has 0 processes with total weight 0
CPU 5 has 1 processes with total weight 1
CPU 6 has 107 processes with total weight 107
CPU 7 has 81 processes with total weight 81

CPU 0 has 2 processes with total weight 2
CPU 1 has 1 processes with total weight 1
CPU 2 has 110 processes with total weight 110
CPU 3 has 0 processes with total weight 0
CPU 4 has 1 processes with total weight 1
CPU 5 has 110 processes with total weight 110
CPU 6 has 1 processes with total weight 1
CPU 7 has 0 processes with total weight 0

CPU 0 has 57 processes with total weight 57
CPU 1 has 99 processes with total weight 99
CPU 2 has 2 processes with total weight 2
CPU 3 has 165 processes with total weight 165
CPU 4 has 38 processes with total weight 38
CPU 5 has 5 processes with total weight 5
CPU 6 has 299 processes with total weight 299
CPU 7 has 76 processes with total weight 76

CPU 0 has 1 processes with total weight 1
CPU 1 has 42 processes with total weight 42
CPU 2 has 1 processes with total weight 1
CPU 3 has 1 processes with total weight 1
CPU 4 has 0 processes with total weight 0
CPU 5 has 0 processes with total weight 0
CPU 6 has 0 processes with total weight 0
CPU 7 has 1 processes with total weight 1

CPU 0 has 48 processes with total weight 48
CPU 1 has 239 processes with total weight 239
CPU 2 has 2 processes with total weight 2
CPU 3 has 239 processes with total weight 239
CPU 4 has 39 processes with total weight 39
CPU 5 has 239 processes with total weight 239
CPU 6 has 2 processes with total weight 2
CPU 7 has 239 processes with total weight 239

* New processes have been just spawned on CPU0, hence the overload. This would be reallocated 
as soon as select_task is called by core.c

CPU 0 has 101 processes with total weight 101
CPU 1 has 1 processes with total weight 1
CPU 2 has 6 processes with total weight 6
CPU 3 has 6 processes with total weight 6
CPU 4 has 6 processes with total weight 6
CPU 5 has 7 processes with total weight 7
CPU 6 has 6 processes with total weight 6
CPU 7 has 6 processes with total weight 6

```
### Test heavy load
Large number of processes is expected to slow down the system, but should not result in system crash.

##### Steps of Test
* Run test program to keep monitoring wrr workload allocation.
* Open as many apps as possible and keep them running, for example, use calculator to do the math while a mail is sending in the background.

##### Expected Results
```
CPU 0 has 213 processes with total weight 213
CPU 1 has 213 processes with total weight 213
CPU 2 has 213 processes with total weight 213
CPU 3 has 213 processes with total weight 213
CPU 4 has 89 processes with total weight 89
CPU 5 has 213 processes with total weight 213
CPU 6 has 1 processes with total weight 1
CPU 7 has 135 processes with total weight 135

CPU 0 has 108 processes with total weight 108
CPU 1 has 1 processes with total weight 1
CPU 2 has 2 processes with total weight 2
CPU 3 has 108 processes with total weight 108
CPU 4 has 0 processes with total weight 0
CPU 5 has 1 processes with total weight 1
CPU 6 has 107 processes with total weight 107
CPU 7 has 81 processes with total weight 81

CPU 0 has 2 processes with total weight 2
CPU 1 has 1 processes with total weight 1
CPU 2 has 110 processes with total weight 110
CPU 3 has 0 processes with total weight 0
CPU 4 has 1 processes with total weight 1
CPU 5 has 110 processes with total weight 110
CPU 6 has 1 processes with total weight 1
CPU 7 has 0 processes with total weight 0

CPU 0 has 57 processes with total weight 57
CPU 1 has 99 processes with total weight 99
CPU 2 has 2 processes with total weight 2
CPU 3 has 165 processes with total weight 165
CPU 4 has 38 processes with total weight 38
CPU 5 has 5 processes with total weight 5
CPU 6 has 299 processes with total weight 299
CPU 7 has 76 processes with total weight 76
```

