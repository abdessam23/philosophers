#include "philo.h"

void check_dead(t_table *tab)
{
     
}

void    ft_eat(philo_t *philo)
{
    t_table *tab;
    tab = philo->data;
    pthread_mutex_lock(&philo->fork);
    ft_print(philo, FRK);
    if (philo->data->n_ph == 1)
    {
        ft_sleep(philo, tab->td);
        ft_print(philo, MSG_RP);
        pthread_mutex_unlock(&philo->fork);
        tab->died = 1;
        return;
    }
    pthread_mutex_lock(&philo->r_phi->fork);
    ft_print(philo, FRK);
    pthread_mutex_lock(&tab->check);
    philo->c_eat++;
    ft_print(philo, EAT);
    philo->last_time = get_time();
    pthread_mutex_unlock(&tab->check);
    ft_sleep(tab, tab->te);
    pthread_mutex_unlock(&philo->r_phi->fork);
    pthread_mutex_unlock(&philo->fork);
}

void *routine(void *arg)
{
    t_table *tab;
    philo_t *philo;
    
    philo  = (philo_t *) arg;
    tab = philo->data;
    if (philo->id % 2 ==0)
        usleep(1000);
    while (!tab->died && !tab->m_eaten)
    {
        ft_eat(philo);
        ft_print(philo,SLP);
        ft_sleep(tab,tab->ts);
        ft_print(philo,TNK);
    }
    return (NULL);
}