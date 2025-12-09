#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	num;

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
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%d %s \n",philo->id,s);
	pthread_mutex_unlock(&philo->data->print_lock);
}

long	get_current_time()
{
	struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000L); // milisaniye cinsinden
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(10);
	return (0);
}

void	*monitor_func(void *arg)
{
	long	current_time;
	int		i;
	t_philo	*philos;
	t_data	*my_data;

	philos = (t_philo*)arg;
	my_data = philos[0].data;

	while (1)
	{
		i = 0;
		while (i < my_data->num_philo)
		{
			pthread_mutex_lock(&philos[i].data->meal_lock);
			current_time = get_current_time();
			if (current_time - philos[i].last_time_eat > my_data->time_die)
			{
				pthread_mutex_lock(&philos[i].data->dead_lock);
				philos[i].data->dead = 1;
				my_print(&philos[i], "is dead");
				pthread_mutex_unlock(&philos[i].data->dead_lock);
				pthread_mutex_unlock(&philos[i].data->meal_lock);
				return NULL;
			}
			pthread_mutex_unlock(&philos[i].data->meal_lock);
			i++;
		}
		ft_usleep(1);
	}
	return NULL;
}
