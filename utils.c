#include "philo.h"

void    init_tdata(t_data *data, char **arg)
{
    data->num_philo = ft_atoi(arg[1]);
    data->time_die = ft_atoi(arg[2]);
    data->time_eat = ft_atoi(arg[3]);
    data->time_sleep = ft_atoi(arg[4]);
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
        return 1;
    while (i < data->num_philo)
    {
        pthread_mutex_init(&data->forks[i],NULL);
        i++;
    }
}