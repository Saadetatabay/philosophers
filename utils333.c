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

void my_print(t_philo *philo, char *s)
{
    long timestamp;

    pthread_mutex_lock(&philo->data->dead_lock);
    // DÜZELTME: "died" mesajı hariç diğer mesajları bastır
    if (philo->data->dead)
    {
        // Sadece ölüm mesajına izin ver
        if (s[0] != 'd' || s[1] != 'i' || s[2] != 'e' || s[3] != 'd')
        {
            pthread_mutex_unlock(&philo->data->dead_lock);
            return;
        }
    }
    pthread_mutex_unlock(&philo->data->dead_lock);

    pthread_mutex_lock(&philo->data->print_lock);
    timestamp = get_current_time() - philo->data->start_time;
    printf("%ld %d %s\n", timestamp, philo->id, s);
    pthread_mutex_unlock(&philo->data->print_lock);
}

long	get_current_time()
{
	struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(500);
	return (0);
}

int	all_ate(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->meal_lock);
	while (i < data->num_philo)
	{
		if (data->philos[i].eat_count < data->must_eat)
		{
			pthread_mutex_unlock(&data->meal_lock);
			return 0;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (1);
}

void	*monitor_func(void *arg)
{
	long	current_time;
	int		i;
	t_data *data = (t_data *)arg;  // DÜZELTME: Doğrudan data olarak al
    t_philo *philos = data->philos;

	while (1)
	{
		i = 0;
		// Açlıktan öldü mü kontrolü
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->meal_lock);
			current_time = get_current_time();
			if (current_time - philos[i].last_time_eat > data->time_die)
			{
				pthread_mutex_lock(&data->dead_lock);
    			data->dead = 1;
				pthread_mutex_unlock(&data->dead_lock);
				pthread_mutex_unlock(&data->meal_lock);
				
				// Ölüm mesajını kilitsiz yazdır
				my_print(&philos[i], "died");
				return NULL;
			}
			pthread_mutex_unlock(&data->meal_lock);
			i++;
		}
		
		// Must eat kontrolü
		if (data->must_eat != -1)
		{
			if (all_ate(data))
			{
				pthread_mutex_lock(&data->dead_lock);
        		data->dead = 1;
        		pthread_mutex_unlock(&data->dead_lock);
				return NULL;
			}
		}
		usleep(1000);  // CPU kullanımını azaltmak için
	}
	return NULL;
}
