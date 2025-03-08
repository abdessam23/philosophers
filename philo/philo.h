/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:42:36 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/08 10:36:43 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				c_eat;
	size_t			last_eat;
	pthread_mutex_t	fork;
	struct s_table	*data;
	struct s_philo	*r_phi;
	struct s_philo	*l_phi;

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
	pthread_t		*threads;
	t_philo			*philos;
	pthread_mutex_t	check;
	pthread_mutex_t	print;
}					t_table;

int					ft_atoi(char *str);
size_t				get_time(void);
void				ft_error(char *str);
int					ft_strcmp(char *s1, char *s2);
void				*routine(void *arg);
void				is_valid(char **str);
void				init_table(t_table *tab);
void				ft_init(t_table *p, int ac, char **argv);
void				check_dead(t_table *tab);
void				ft_sleep(t_table *tab, int ts);
void				ft_print(t_philo *philo, char *str);
void				stop_simulation(t_table *tab, pthread_t *th);

#endif
