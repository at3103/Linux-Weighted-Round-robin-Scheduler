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

## Recommended Test Scenarios
