/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 20:58:41 by satabay           #+#    #+#             */
/*   Updated: 2026/02/24 21:21:41 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philo == 1)
		return (my_print(philo, "has taken a fork"),
			ft_usleep(philo->data->time_die), NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_eat);
	else if (philo->data->num_philo % 2 != 0
		&& philo->id == philo->data->num_philo)
		ft_usleep(philo->data->time_eat / 2);
	while (!should_stop(philo))
	{
		my_print(philo, "is thinking");
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		if (should_stop(philo))
			return (NULL);
		my_print(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep);
	}
	return (NULL);
}

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
		my_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		my_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		my_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		my_print(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	my_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_time_eat = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_eat);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
