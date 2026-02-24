/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 20:53:13 by satabay           #+#    #+#             */
/*   Updated: 2026/02/24 21:21:59 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	if (philo->data->must_eat != -1
		&& philo->eat_count >= philo->data->must_eat)
		return (1);
	return (0);
}

int	check_num(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if ((argc == 5 || argc == 6) && check_num(argv))
	{
		init_tdata(&data, argv);
		init_forks(&data);
		philo_init(&data);
		init_thread(&data);
		cleanup(&data);
	}
	else
	{
		printf("yanlis arg");
	}
}
