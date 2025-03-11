/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:30:12 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/11 11:56:18 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				c_eat;
	size_t			last_eat;
	pthread_t		check_die;
	struct s_table	*tab;
	struct s_philo	*r_phi;
	struct s_philo	*l_phi;
	pid_t			pid;
}					t_philo;

typedef struct s_table
{
	int				n_ph;
	int				td;
	int				te;
	int				ts;
	int				nt;
	int				n_eat;
	int				m_eaten;
	int				died;
	size_t			s_time;
	t_philo			*philos;
	sem_t			*check;
	sem_t			*print;
	sem_t			*forks;
}					t_table;

int					ft_atoi(char *str);
int					ft_strcmp(char *s1, char *s2);
size_t				get_time(void);
void				ft_error(char *str);
void				ft_sleep(t_table *tab, int ts);
void				ft_print(t_philo *philo, char *str);
void				*check_dead(void *arg);
void				init_table(t_table *tab);
void				ft_init(t_table *p, int ac, char **argv);
void				*philo_life(void *arg);
void				exit_philo(t_table *tab);

#endif
