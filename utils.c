#include "philo.h"

void    init_tdata(t_data data, char **arg, int argc)
{
    data.num_philo = ft_atoi(arg[1]);
    data.time_die = ft_atoi(arg[2]);
    data.time_eat = ft_atoi(arg[3]);
    data.time_sleep = ft_atoi(arg[4]);
    if (argc == 6)
        data.must_eat = ft_atoi(arg[4]);
    else
        data.ust_eat = -1;
}