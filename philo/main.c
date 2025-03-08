/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:24:50 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/08 10:27:09 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
}

static void	isvalid_init(t_table *tab, int ac, char **argv)
{
	is_valid(argv);
	tab->s_time = get_time();
	ft_init(tab, ac, argv);
}

static void	lock_check(t_table *tab, int i)
{
	pthread_mutex_lock(&tab->check);
	tab->philos[i].last_eat = tab->s_time;
	pthread_mutex_unlock(&tab->check);
}

int	main(int ac, char **argv)
{
	t_table		p;
	pthread_t	*t;
	int			i;

	i = -1;
	if (ac == 5 || ac == 6)
	{
		isvalid_init(&p, ac, argv);
		t = malloc(sizeof(pthread_t) * (p.n_ph));
		while (++i < p.n_ph)
		{
			if (pthread_create(&t[i], NULL, routine, &p.philos[i]))
			{
				free(p.philos);
				free(t);
				ft_error("cannot create a thread.");
			}
			lock_check(&p, i);
		}
		check_dead(&p);
		stop_simulation(&p, t);
	}
	else
		ft_error("Error : must to put at least 5 arguments.");
	return (0);
}
