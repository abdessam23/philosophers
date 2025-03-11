/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:02:19 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/11 15:59:56 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_dead(void *arg)
{
	t_philo	*philo;
	t_table	*tab;

	philo = (t_philo *)arg;
	tab = philo->tab;
	while (1)
	{
		sem_wait(tab->check);
		if (get_time() - philo->last_eat > (size_t)tab->td)
		{
			ft_print(philo, "died");
			sem_wait(tab->print);
			tab->died = 1;
			exit(1);
		}
		sem_post(tab->check);
		if (tab->died)
			break ;
		usleep(1000);
		if (tab->nt != -1 && philo->c_eat >= tab->nt)
			break ;
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	t_table	*tab;

	tab = philo->tab;
	sem_wait(philo->tab->forks);
	ft_print(philo, "has taking fork");
	if (philo->tab->n_ph == 1)
	{
		ft_sleep(tab, tab->td);
		ft_print(philo, "died");
		tab->died = 1;
		return ;
	}
	sem_wait(philo->tab->forks);
	ft_print(philo, "has taking fork");
	sem_wait(philo->tab->check);
	philo->c_eat++;
	ft_print(philo, "is eating");
	philo->last_eat = get_time();
	sem_post(philo->tab->check);
	ft_sleep(tab, tab->te);
	sem_post(philo->tab->forks);
	sem_post(philo->tab->forks);
}

void	*philo_life(void *arg)
{
	t_table	*tab;
	t_philo	*philo;

	philo = (t_philo *)arg;
	tab = philo->tab;
	philo->last_eat = tab->s_time;
	pthread_create(&philo->check_die, NULL, check_dead, (void *)philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!tab->died)
	{
		ft_eat(philo);
		if (tab->nt != -1 && philo->c_eat >= tab->nt)
			break ;
		ft_print(philo, "is sleeping");
		ft_sleep(tab, tab->ts);
		ft_print(philo, "is thinking");
	}
	pthread_join(philo->check_die, NULL);
	exit(1);
}
