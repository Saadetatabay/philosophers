#include "philo.h"

void *philo_func(void *arg)
{
    t_philo *philo = (t_philo*)arg;
    if (philo->id % 2 == 0)
        ft_usleep(10); // Çiftler hafif bekler

    while (!over(philo))
    {
        if (!take_forks(philo)) break; // Çatal alamazsa (bir öldüyse) dur
        
        eat(philo);
        put_forks(philo); // Çatalları her durumda bırakmalı
        
        if (over(philo)) break;

        my_print(philo, "is sleeping");
        ft_usleep(philo->data->time_sleep);
        
        my_print(philo, "is thinking");
		usleep(100);
    }
    return NULL;
}

// void    *philo_func(void *arg)
// {
//     t_philo *philo = (t_philo*)arg; //*philo benim gönderdiğim  philomun struct yapıs
//     if (philo->id % 2 == 0)
//         ft_usleep(50);
//     while(1)
//     {
// 		if (over(philo))
// 			break;
		
// 		// pthread_mutex_lock(&philo->data->dead_lock);
// 		// if(philo->data->dead)
// 		// {
// 		// 	pthread_mutex_unlock(&philo->data->dead_lock);
// 		// 	// philo_func, break tatbikinden sonra hemen:
// 		// 	break;
// 		// }
// 		//pthread_mutex_unlock(&philo->data->dead_lock);
//         take_forks(philo);
// 		if (over(philo))
// 		{
// 			put_forks(philo);
// 			break;
// 		}
//         eat(philo);
// 		put_forks(philo);
// 		if (over(philo))
// 			break;
//         sleep_philo(philo);
// 		my_print(philo,"is thinking");
//     }
// 	printf("[DEBUG] philo %d exiting thread (dead=%d)\n", philo->id, philo->data->dead);
//     return NULL;
// }

int over(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->dead_lock);
    if (philo->data->dead)
    {
        pthread_mutex_unlock(&philo->data->dead_lock);
        return 1;
    }
    pthread_mutex_unlock(&philo->data->dead_lock);
    return 0;
}

// int	check_dead(t_philo	*philo)
// {
// 	long	current_time;
	
// 	current_time = get_current_time();
// 	pthread_mutex_lock(&philo->data->meal_lock);
// 	if (current_time - philo->last_time_eat > philo->data->time_die)
// 	{
// 		printf("control\n");
// 		pthread_mutex_lock(&philo->data->dead_lock);
// 		philo->data->dead = 1;
// 		my_print(philo, "is dead");
// 		pthread_mutex_unlock(&philo->data->dead_lock);
// 		pthread_mutex_unlock(&philo->data->meal_lock);
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&philo->data->meal_lock);
// 	return 0;
// }

// void	take_forks(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->dead_lock);
// 	if (philo->data->dead)
// 	{
// 		pthread_mutex_unlock(&philo->data->dead_lock);
// 		return ;
// 	}
// 	pthread_mutex_unlock(&philo->data->dead_lock);
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->right_fork);
// 		my_print(philo , "has taken a fork");
// 		pthread_mutex_lock(philo->left_fork);
// 		my_print(philo , "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		my_print(philo , "has taken a fork");
// 		pthread_mutex_lock(philo->right_fork);
// 		my_print(philo , "has taken a fork");
// 	}
// }

int take_forks(t_philo *philo) // void yerine int yapıldı
{
    if (over(philo)) return (0);

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        my_print(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        my_print(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        my_print(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        my_print(philo, "has taken a fork");
    }
    return (1);
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