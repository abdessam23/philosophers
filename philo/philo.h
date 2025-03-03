#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table t_table;
typedef struct s_philo
{
    int id;
    int l_meal_time;
    int c_eat;
    size_t last_time;
    pthread_mutex_t *fork;
    t_table *data;
    struct s_philo *r_phi;
    struct s_philo *l_phi;
    
} philo_t;
 
typedef struct s_table
{
    int n_ph;
    long td;
    long te;
    long ts;
    int nt;
    int is_eating;
    int m_eaten;
    pthread_t *threads;
    philo_t *philos;
    pthread_mutex_t check;
    pthread_mutex_t print;
    int died;
    size_t s_time;
    double diff;
} t_table;
int     ft_atoi(char *str);
void    ft_error(char *str);
void    *routine(void *arg);
void    ft_init(t_table *p,int ac, char **argv);

/*
//----------------------------------------//
void monitor_philosophers(t_table *data);
void *philosopher_routine(void *arg);
//----------------------------------------//
void ft_usleep(int time);
*/

#endif