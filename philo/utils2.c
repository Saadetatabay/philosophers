/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:42:37 by satabay           #+#    #+#             */
/*   Updated: 2026/03/06 13:43:30 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *nptr)
{
	long	sign;
	long	num;

	num = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = 10 * num + *nptr - '0';
		nptr++;
	}
	return (sign * num);
}

void	my_print(t_philo *philo, char *s)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	timestamp = get_current_time() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, s);
	pthread_mutex_unlock(&philo->data->print_lock);
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int	ft_usleep(size_t ms, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
	{
		if (should_stop(philo))
			return (1);
		usleep(500);
	}
	return (0);
}

int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->must_eat == -1)
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	i = 0;
	all_ate = 1;
	while (i < data->num_philo)
	{
		if (data->philos[i].eat_count < data->must_eat)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (all_ate);
}
