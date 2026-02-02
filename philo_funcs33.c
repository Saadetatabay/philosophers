#include "philo.h"

void *philo_func(void *arg)
{
    t_philo *philo = (t_philo*)arg;
    
    // Çift ID'li filozoflar biraz beklesin (deadlock önleme)
    if (philo->id % 2 == 0)
        usleep(1000);

    while (!over(philo))
    {
        // Çatal almayı dene
        if (!take_forks(philo))
            break;
        
        // Yemek ye
        eat(philo);
        
        // Çatalları bırak
        put_forks(philo);
        
        // Tekrar kontrol
        if (over(philo))
            break;

        // Uyu
        my_print(philo, "is sleeping");
        ft_usleep(philo->data->time_sleep);
        
        if (over(philo))
            break;
            
        // Düşün
        my_print(philo, "is thinking");
    }
    return NULL;
}

int over(t_philo *philo)
{
    int is_dead;
    
    pthread_mutex_lock(&philo->data->dead_lock);
    is_dead = philo->data->dead;
    pthread_mutex_unlock(&philo->data->dead_lock);
    
    return is_dead;
}

int take_forks(t_philo *philo)
{
    // Önce kontrol et
    if (over(philo))
        return (0);

    // Deadlock önlemek için çift/tek ID'ye göre farklı sırada kilitle
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        if (over(philo))
        {
            pthread_mutex_unlock(philo->right_fork);
            return (0);
        }
        my_print(philo, "has taken a fork");
        
        pthread_mutex_lock(philo->left_fork);
        if (over(philo))
        {
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            return (0);
        }
        my_print(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        if (over(philo))
        {
            pthread_mutex_unlock(philo->left_fork);
            return (0);
        }
        my_print(philo, "has taken a fork");
        
        pthread_mutex_lock(philo->right_fork);
        if (over(philo))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return (0);
        }
        my_print(philo, "has taken a fork");
    }
    return (1);
}

void	eat(t_philo *philo)
{
	my_print(philo, "is eating");
	
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_time_eat = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	
	ft_usleep(philo->data->time_eat);
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
