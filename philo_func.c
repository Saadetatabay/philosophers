#include "philo.h"

void *philo_func(void *arg)
{
    t_philo *philo = (t_philo*)arg;
    
    // Tek filozof özel durumu
    if (philo->data->num_philo == 1)
    {
        my_print(philo, "has taken a fork");
        usleep(philo->data->time_die * 1000);
        return NULL;
    }
    
    // Çift ID'liler biraz beklesin (deadlock önleme)
    if (philo->id % 2 == 0)
        usleep(100);

    while (1)
    {
        // Ölüm kontrolü
        if (is_dead(philo))
            break;
        
        // Düşün
        my_print(philo, "is thinking");
        
        // Çatalları al
        take_forks(philo);
        
        // Tekrar kontrol (çatal alırken ölebilir)
        if (is_dead(philo))
        {
            put_forks(philo);
            break;
        }
        
        // Ye
        eat(philo);
        
        // Çatalları bırak
        put_forks(philo);
        
        // Kontrol
        if (is_dead(philo))
            break;

        // Uyu
        my_print(philo, "is sleeping");
        ft_usleep(philo->data->time_sleep);
    }
    return NULL;
}

int is_dead(t_philo *philo)
{
    int dead;
    
    pthread_mutex_lock(&philo->data->dead_lock);
    dead = philo->data->dead;
    pthread_mutex_unlock(&philo->data->dead_lock);
    
    return dead;
}

void take_forks(t_philo *philo)
{
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
