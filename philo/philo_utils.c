/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:13:59 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/12 15:17:56 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_simulation(t_table *tab, pthread_t *th)
{
	int	i;

	i = -1;
	while (++i < tab->n_ph)
		pthread_join(th[i], NULL);
	i = -1;
	while (++i < tab->n_ph)
		pthread_mutex_destroy(&tab->philos[i].fork);
	pthread_mutex_destroy(&tab->check);
	pthread_mutex_destroy(&tab->print);
	free(tab->philos);
	free(th);
}

void	ft_sleep(t_table *tab, int ts)
{
	size_t	t;

	t = get_time();
	while (!tab->died)
	{
		if (get_time() - t >= (size_t)ts)
			break ;
		usleep(100);
	}
}

void	ft_print(t_philo *philo, char *str)
{
	int	t;

	t = get_time() - philo->data->s_time;
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->died && !philo->data->m_eaten)
	{
		printf("%d %d %s", t, philo->id, str);
		if (ft_strcmp(str, "is eating 🍜​") == 0)
			printf(" #%d", philo->c_eat);
		printf("\n");
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	init_table(t_table *tab)
{
	int	i;

	i = -1;
	tab->m_eaten = 0;
	tab->died = 0;
	tab->philos = (t_philo *)malloc((size_t)tab->n_ph * sizeof(t_philo));
	if (!tab->philos)
		return ;
	while (++i < tab->n_ph)
	{
		tab->philos[i].id = i + 1;
		tab->philos[i].data = tab;
		tab->philos[i].c_eat = 0;
		if (i + 1 == tab->n_ph)
			tab->philos[i].r_phi = &tab->philos[0];
		else
			tab->philos[i].r_phi = &tab->philos[i + 1];
		if (i == 0)
			tab->philos[i].l_phi = &tab->philos[tab->n_ph - 1];
		else
			tab->philos[i].l_phi = &tab->philos[i - 1];
		pthread_mutex_init(&tab->philos[i].fork, NULL);
	}
	pthread_mutex_init(&tab->check, NULL);
	pthread_mutex_init(&tab->print, NULL);
}
