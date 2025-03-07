#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
    int id;
    //int l_meal_time;
    int c_eat;
    size_t last_eat;
    pthread_mutex_t fork;
    struct s_table *data;
    struct s_philo *r_phi;
    struct s_philo *l_phi;
    
} philo_t;
 
typedef struct s_table
{
    int n_ph;
    int td;
    int te;
    int ts;
    int nt;
    int n_eat;
    int m_eaten;
    int died;
    size_t s_time;
    pthread_t *threads;
    philo_t *philos;
    pthread_mutex_t check;
    pthread_mutex_t print;
} t_table;
int     ft_atoi(char *str);
void    ft_error(char *str);
void    *routine(void *arg);
size_t  get_time();
void    ft_init(t_table *p,int ac, char **argv);
void    check_dead(t_table *tab);
void    ft_sleep(t_table *tab ,int ts);
void    ft_print(philo_t *philo, char *str);
void    stop_simulation(t_table *tab, pthread_t *th);
/*
//----------------------------------------//
void monitor_philosophers(t_table *data);
void *philosopher_routine(void *arg);
//----------------------------------------//
void ft_usleep(int time);
*/

#endif