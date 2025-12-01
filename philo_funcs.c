#include "philo.h"

void    *philo_func(void *arg)
{
    t_philo *philo = (t_philo*)arg; //*philo benim gönderdiğim  philomun struct yapıs
    if (philo->id % 2 == 0)
        usleep(500);
    while(!philo->data->dead)
    {
		if(check_dead(philo))
			break;
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
        think(philo);
    }
    return NULL;
}

int	check_dead(t_philo	*philo)
{
	long	current_time;
	
	current_time = get_current_time();
	pthread_mutex_lock(&philo->data->dead_lock);
	if (current_time - philo->last_time_eat > philo->data->time_die)
	{
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return 0;
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		my_print("has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		my_print("has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		my_print("has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		my_print("has taken a fork");
	}
}