/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_utlis_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:42:09 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/10 14:04:30 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	exit_philo(t_table *tab)
{
	int	i;
	int	status;

	i = -1;
	while (++i < tab->n_ph)
	{
		waitpid(-1, &status, 1);
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < tab->n_ph)
				kill(tab->philos[i].pid, SIGTERM);
			break ;
		}
	}
	sem_close(tab->print);
	sem_close(tab->check);
	sem_close(tab->forks);
	sem_unlink("/sem_check");
	sem_unlink("/sem_print");
	sem_unlink("/sem_forks");
	free(tab->philos);
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
	sem_wait(philo->data->print);
	if (!philo->data->died && !philo->data->m_eaten)
	{
		printf("%d %d %s", t, philo->id, str);
		if (ft_strcmp(str, "is eating") == 0)
			printf(" (Meal #%d)", philo->c_eat);
		printf("\n");
	}
	sem_post(philo->data->print);
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
	}
}
