/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 20:58:41 by satabay           #+#    #+#             */
/*   Updated: 2026/02/25 20:39:12 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->data->dead_lock);
	dead = philo->data->dead;
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (dead);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		if (should_stop(philo))
		{
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		my_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		my_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (should_stop(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			return ;
		}
		my_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		my_print(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	if (should_stop(philo))
		return ;
	my_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_time_eat = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_eat);
}

void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	think(t_philo *philo)
{
	long	think_time;

	my_print(philo, "is thinking");
	if (philo->data->num_philo % 2 != 0)
	{
		think_time = philo->data->time_eat * 2 - philo->data->time_sleep;
		if (think_time < 0)
			think_time = 0;
		if (think_time > philo->data->time_die / 2)
			think_time = philo->data->time_die / 2;
		ft_usleep(think_time);
	}
}
