/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:13:59 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/06 15:47:43 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    stop_simulation(t_table *tab, pthread_t *th)
{
    int i;
    
    i = -1;
    while (++i < tab->n_ph)
        pthread_join(th[i], NULL);
    i = -1;
    while(++i < tab->n_ph)
        pthread_mutex_destroy(&tab->philos[i].fork);
    pthread_mutex_destroy(&tab->check);
    pthread_mutex_destroy(&tab->print);
    free(tab->philos);
    free(th);
}

void    ft_sleep(t_table *tab ,int ts)
{
    size_t t;
    t = get_time();
    while(!tab->died)
    {
        if (get_time() - t >= ts)
            break;
        usleep(100);
    }
}
