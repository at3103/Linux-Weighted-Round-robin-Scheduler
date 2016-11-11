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
Result and comments goes here.
```
### Test on different weights
The weight controls the frequency of reschedule. Generally speaking, larger weight discourages multi-process while smaller weight magnifies reschedule overhead.

##### Steps of Test
* Use test program to set weight to 1, then simply play around with the phone;
* Use test program to set weight to 1000, then try multi-process by opening up google play store while browser is loading a page.

##### Expected Results
```
Result and comments goes here.
```
### Test load balancing
The load balancing mechanism is expected to allocate workload evenly across multiple cores, even under scenarios where non-trivial number of processes are spawned.

##### Steps of Test
* Run test program to keep monitoring wrr workload allocation.
* Open Chrome, which will spawn several processes simutaniously.

##### Expected Results
```
Result and comments goes here.
```
### Test heavy load
Large number of processes is expected to slow down the system, but should not result in system crash.

##### Steps of Test
* Run test program to keep monitoring wrr workload allocation.
* Open as many apps as possible and keep them running, for example, use calculator to do the math while a mail is sending in the background.

##### Expected Results
```
Result and comments goes here.
```
