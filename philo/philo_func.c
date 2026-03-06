/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:58:26 by satabay           #+#    #+#             */
/*   Updated: 2026/03/06 13:42:12 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philo == 1)
		return (my_print(philo, "has taken a fork"),
			ft_usleep(philo->data->time_die, philo), NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_eat / 2, philo);
	while (!should_stop(philo))
	{
		think(philo);
		take_forks(philo);
		if (should_stop(philo))
			return (NULL);
		eat(philo);
		put_forks(philo);
		my_print(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep, philo);
	}
	return (NULL);
}
