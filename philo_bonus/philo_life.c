/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:02:19 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/09 15:55:23 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_dead(t_table *tab)
{
	int	i;

	while (!tab->m_eaten)
	{
		i = -1;
		while (!tab->died && ++i < tab->n_ph)
		{
			sem_wait(&tab->check);
			if (get_time() - tab->philos[i].last_eat > (size_t)tab->td)
			{
				ft_print(&tab->philos[i], "died");
				tab->died = 1;
			}
			sem_post(&tab->check);
			usleep(100);
		}
		if (tab->died)
			break ;
		i = 0;
		while (tab->nt != -1 && i < tab->n_ph
			&& tab->philos[i].c_eat >= tab->nt)
			i++;
		if (i == tab->n_ph)
			tab->m_eaten = 1;
	}
}

void	ft_eat(t_philo *philo)
{
	t_table	*tab;

	tab = philo->data;
	sem_wait(&philo->fork);
	ft_print(philo, "has taking fork");
	if (philo->data->n_ph == 1)
	{
		ft_sleep(tab, tab->td);
		ft_print(philo, "died");
		sem_post(&philo->fork);
		tab->died = 1;
		return ;
	}
	sem_wait(&philo->r_phi->fork);
	ft_print(philo, "has taking fork");
	sem_wait(&tab->check);
	philo->c_eat++;
	ft_print(philo, "is eating");
	philo->last_eat = get_time();
	sem_post(&tab->check);
	ft_sleep(tab, tab->te);
	sem_post(&philo->r_phi->fork);
	sem_post(&philo->fork);
}

void	*philo_life(void *arg)
{
	t_table	*tab;
	t_philo	*philo;

	philo = (t_philo *)arg;
	tab = philo->data;
    philo->last_eat = tab->s_time;
    pthread_create(&philo->check_die, NULL, check_dead, (void *) philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!tab->died && !tab->m_eaten)
	{
		ft_eat(philo);
		ft_print(philo, "is sleeping");
		ft_sleep(tab, tab->ts);
		ft_print(philo, "is thinking");
	}
    pthread_join(philo->check_die, NULL);
	exit(1);
}
