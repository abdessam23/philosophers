/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:42:52 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/11 15:03:18 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_dead(t_table *tab)
{
	int	i;

	while (!tab->m_eaten)
	{
		i = -1;
		while (!tab->died && ++i < tab->n_ph)
		{
			pthread_mutex_lock(&tab->check);
			if (get_time() - tab->philos[i].last_eat > (size_t)tab->td)
			{
				ft_print(&tab->philos[i], "died");
				tab->died = 1;
			}
			pthread_mutex_unlock(&tab->check);
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
	pthread_mutex_lock(&philo->fork);
	ft_print(philo, "has taking fork");
	if (philo->data->n_ph == 1)
	{
		ft_sleep(tab, tab->td);
		ft_print(philo, "died");
		pthread_mutex_unlock(&philo->fork);
		tab->died = 1;
		return ;
	}
	pthread_mutex_lock(&philo->r_phi->fork);
	ft_print(philo, "has taking fork");
	pthread_mutex_lock(&tab->check);
	philo->c_eat++;
	ft_print(philo, "is eating");
	philo->last_eat = get_time();
	pthread_mutex_unlock(&tab->check);
	ft_sleep(tab, tab->te);
	pthread_mutex_unlock(&philo->r_phi->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	*routine(void *arg)
{
	t_table	*tab;
	t_philo	*philo;

	philo = (t_philo *)arg;
	tab = philo->data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!tab->died && !tab->m_eaten)
	{
		ft_eat(philo);
		ft_print(philo, "is sleeping");
		ft_sleep(tab, tab->ts);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}
