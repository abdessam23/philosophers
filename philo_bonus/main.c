/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:25:10 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/08 17:31:47 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int main(int ac , char **argv)
{
    if (ac == 5 || ac == 6)
	{
			
	}
	else
		ft_error("wrong input");
	return (0);
}