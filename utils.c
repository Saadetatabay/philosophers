#include "philo.h"

void    init_tdata(t_data *data, char **arg)
{
	data->dead = 0;
    data->num_philo = ft_atoi(arg[1]);
    data->time_die = ft_atoi(arg[2]);
    data->time_eat = ft_atoi(arg[3]);
    data->time_sleep = ft_atoi(arg[4]);
	//data->start_time = get_current_time();
    if (arg[5])
        data->must_eat = ft_atoi(arg[5]);
    else
        data->must_eat = -1;
}

void    init_forks(t_data *data)
{
    int i;

    i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
    if (!data->forks)
        printf("hata");
    while (i < data->num_philo)
    {
        pthread_mutex_init(&data->forks[i],NULL);
        i++;
    }
	pthread_mutex_init(&data->print_lock,NULL);
	pthread_mutex_init(&data->meal_lock,NULL);
	pthread_mutex_init(&data->dead_lock,NULL);
}

void	philo_init(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo)* data->num_philo);
	if (!philos)
		return ;
	
	data->philos = philos;
	while (i < data->num_philo)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_time_eat = 0;
		philos[i].data = data;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		i++;
	}
}

int	init_thread(t_data *data)
{
	pthread_t	monitor_thrd;
	int			i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->num_philo)
    {
        data->philos[i].last_time_eat = data->start_time; // Şimdi doğru değere eşitlendi
        i++;
    }

	i = 0;
	pthread_create(&monitor_thrd, NULL, monitor_func, data->philos);
	while (i < data->num_philo)
	{
		pthread_create(&data->philos[i].thread, NULL, philo_func, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thrd, NULL);
	return (0);
}