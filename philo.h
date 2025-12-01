#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			must_eat;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t print_lock;  // console yazısı için
    pthread_mutex_t meal_lock;   // yeme sayısı kontrolü için
    pthread_mutex_t dead_lock;   // ölüm kontrolü için
}t_data;

typedef struct s_philo
{
	int id;
	int	eat_count;
	long	last_time_eat;
	pthread_t thread;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_data	*data;
} t_philo;


void    *philo_func(void *arg);

#endif