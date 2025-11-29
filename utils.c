#include "philo.h"

void    init_tdata(t_data data, char **arg)
{
    data.num_philo = ft_atoi(arg[1]);
    data.time_die = ft_atoi(arg[2]);
    data.time_eat = ft_atoi(arg[3]);
    data.time_sleep = ft_atoi(arg[4]);
    if (arg[5])
        data.must_eat = ft_atoi(arg[5]);
    else
        data.must_eat = -1;
}