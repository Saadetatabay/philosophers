#include "philo.h"

void    *philo_func(void *arg)
{
    t_philo *philo = (t_philo*)arg; //*philo benim gönderdiğim  philomun struct yapıs
    if (philo->id % 2 == 0)
        usleep(500);
    while(alive())
    {
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
        think(philo);
    }
    return NULL;
}