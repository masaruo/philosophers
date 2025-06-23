# Philosophers project at 42 Tokyo

### environment
* expected to be run by mac

### description
* avoid race condition for threads (by using `mutex`)
* use `semaphore` to avoid race condition for bonus(`process`)

### how to use
* `make` will create executable `philo`
* calling executable by `philo <number of philospers> <time to die> <time to eat> <time to sleep> [number of times each philosopher must eat]`
* i.e. `./philo 3 181 60 60 10`

### how to check race condition
* `fsanitize=thread` to compile
* `valgrind --tool=helgrind`
