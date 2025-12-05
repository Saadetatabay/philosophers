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
