/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:25:10 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/10 14:03:19 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_table *tab)
{
	sem_unlink("/sem_check");
	sem_unlink("/sem_print");
	sem_unlink("/sem_forks");
	tab->forks = sem_open("/sem_forks", O_CREAT, 0644, 1);
	tab->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	tab->check = sem_open("/sem_check", O_CREAT, 0644, tab->n_ph);
	sem_unlink("/sem_check");
	sem_unlink("/sem_print");
	sem_unlink("/sem_forks");
	if (tab->forks == SEM_FAILED || tab->print == SEM_FAILED
		|| tab->check == SEM_FAILED)
		ft_error("Error: sem_open failed.");
}

void	ft_init(t_table *p, int ac, char **argv)
{
	p->n_ph = ft_atoi(argv[1]);
	p->td = ft_atoi(argv[2]);
	p->te = ft_atoi(argv[3]);
	p->ts = ft_atoi(argv[4]);
	p->nt = -1;
	if (ac == 6)
		p->nt = ft_atoi(argv[5]);
	init_table(p);
	init_semaphores(p);
}

static void	isvalid_init(t_table *tab, int ac, char **argv)
{
	is_valid(argv);
	tab->s_time = get_time();
	ft_init(tab, ac, argv);
}

int	main(int ac, char **argv)
{
	int		i;
	t_table	tab;

	i = -1;
	if (ac == 5 || ac == 6)
	{
		isvalid_init(&tab, ac, argv);
		while (++i < tab.n_ph)
		{
			tab.philos[i].pid = fork();
			if (tab.philos[i].pid == -1)
				ft_error("Error : fork failed.");
			if (tab.philos[i].pid == 0)
				philo_life((void *)&tab.philos[i]);
		}
		exit_philo(&tab);
	}
	else
		ft_error("wrong input");
	return (0);
}
