*This project has been created as part of the 42 curriculum by satabay.*

# philosophers

## Description

Philosophers is a classic concurrency problem based on the **Dining Philosophers Problem**, originally formulated by Edsger Dijkstra. The goal is to simulate a scenario where a number of philosophers sit around a circular table, alternating between thinking, eating, and sleeping — while sharing a limited number of forks.

The core challenge is to prevent:
- **Deadlock** — where all philosophers wait for each other indefinitely
- **Starvation** — where a philosopher never gets to eat and dies
- **Data races** — where shared resources are accessed without proper synchronization

Each philosopher is represented by a **thread**, and each fork is protected by a **mutex**. A monitor thread continuously checks whether any philosopher has died or whether all philosophers have eaten the required number of times.

## Instructions

### Requirements

- GCC compiler
- POSIX threads (`-lpthread`)
- Linux or macOS

### Compilation
```bash
make
```

### Execution
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Time a philosopher can go without eating before dying |
| `time_to_eat` (ms) | Time it takes for a philosopher to eat |
| `time_to_sleep` (ms) | Time a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | (Optional) Simulation stops when all philosophers have eaten this many times |

### Examples
```bash

./philo 5 800 200 200

./philo 4 410 200 200 10

./philo 1 800 200 200
```

### Cleanup
```bash
make clean
make fclean
make re
```

## Resources

### Documentation & References

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday — Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)
- [Race Conditions and Mutexes — GeeksForGeeks](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)

### AI Usage

Claude (Anthropic) was used during this project for the following tasks:

- **Debugging**: Identifying race conditions and deadlock scenarios in the monitor and philosopher threads
- **Code review**: Checking mutex lock/unlock ordering to prevent deadlocks between `meal_lock`, `dead_lock`, and `print_lock`
- **Norminette compliance**: Refactoring functions to stay within the 25-line limit without breaking logic
- **Test analysis**: Manually counting eat events from simulation output to verify correctness
- **Optimization**: Improving the philosopher staggering strategy (even/odd ID delays) to prevent starvation with odd numbers of philosophers