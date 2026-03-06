/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:51:34 by satabay           #+#    #+#             */
/*   Updated: 2026/03/06 10:40:11 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			must_eat;
	long			start_time;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_time_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

void	*philo_func(void *arg);
void	my_print(t_philo *philo, char *s);
long	ft_atoi(const char *nptr);
void	init_tdata(t_data *data, char **arg);
void	init_forks(t_data *data);
void	philo_init(t_data *data);
int		init_thread(t_data *data);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	put_forks(t_philo *philo);
long	get_current_time(void);
int		ft_usleep(size_t ms, t_philo *philo);
void	*monitor_func(void *arg);
int		check_all_ate(t_data *data);
int		is_dead(t_philo *philo);
int		should_stop(t_philo *philo);
void	think(t_philo *philo);

#endif
