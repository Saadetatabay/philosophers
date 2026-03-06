/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:42:04 by satabay           #+#    #+#             */
/*   Updated: 2026/03/06 13:42:06 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, int i, long current_time)
{
	if (get_current_time() - data->philos[i].last_time_eat <= data->time_die)
		return (0);
	pthread_mutex_lock(&data->dead_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->dead_lock);
	pthread_mutex_lock(&data->print_lock);
	printf("%ld %d died\n", current_time - data->start_time,
		data->philos[i].id);
	pthread_mutex_unlock(&data->print_lock);
	return (1);
}

void	*monitor_func(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		if (check_all_ate(data))
			return (pthread_mutex_lock(&data->dead_lock),
				data->dead = 1,
				pthread_mutex_unlock(&data->dead_lock), NULL);
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->meal_lock);
			if (check_death(data, i, get_current_time()))
				return (pthread_mutex_unlock(&data->meal_lock), NULL);
			pthread_mutex_unlock(&data->meal_lock);
			i++;
		}
		usleep(300);
	}
}
