#include "philo.h"

void    *philo_func(void *arg)
{
    t_philo *philo = (t_philo*)arg; //*philo benim gönderdiğim  philomun struct yapıs
    if (philo->id % 2 == 0)
        ft_usleep(500);
    while(1)
    {
		pthread_mutex_lock(&philo->data->dead_lock);
		if(philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->dead_lock);
			break;
		}
		pthread_mutex_unlock(&philo->data->dead_lock);
		if (check_dead(philo))
			break;
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
		my_print(philo,"is thinking");
    }
    return NULL;
}

int	check_dead(t_philo	*philo)
{
	long	current_time;
	
	current_time = get_current_time();
	pthread_mutex_lock(&philo->data->meal_lock);
	if (current_time - philo->last_time_eat > philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->dead = 1;
		my_print(philo, "is dead");
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
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
		my_print(philo , "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		my_print(philo , "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		my_print(philo , "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		my_print(philo , "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_time_eat = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	my_print(philo , "is eating");
	ft_usleep(philo->data->time_eat);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_philo(t_philo *philo)
{
	my_print(philo , "is sleeping");
	ft_usleep(philo->data->time_sleep);
}