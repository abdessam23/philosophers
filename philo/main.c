/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:24:50 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/07 14:30:00 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void ft_error(char *str)
{
    printf("%s\n", str);
    exit(1);
}
void is_valid(char **str)
{
    int i = 1;
    while(str[i])
    {
        ft_atoi(str[i]);
        i++;
    }
}
void init_table(t_table *tab)
{
    int i;
    
    i = 0;
    tab->m_eaten = 0;
    tab->died = 0;
    tab->philos = (philo_t *)malloc ((size_t)tab->n_ph * sizeof(philo_t));
    if (!tab->philos)
        return ;
    while (i < tab->n_ph)
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
        i++;
    }
    pthread_mutex_init(&tab->check, NULL);
    pthread_mutex_init (&tab->print, NULL);
}
void ft_init(t_table *p,int ac, char **argv)
{
    p->n_ph =  ft_atoi(argv[1]);
    p->td = ft_atoi(argv[2]);
    p->te = ft_atoi(argv[3]);
    p->ts = ft_atoi(argv[4]);
    p->nt = -1;
    if(ac == 6)
        p->nt = ft_atoi(argv[5]);
    init_table(p);
}

int main(int ac, char **argv)
{
    t_table p;
    pthread_t *t;
    int i;

    i = 0;
    if ( ac == 5 || ac == 6)
    {
        is_valid(argv);
        p.s_time = get_time();
        ft_init(&p, ac, argv);
        t = malloc(sizeof(pthread_t) * (p.n_ph));
        while (i < p.n_ph)
        {
            if(pthread_create(&t[i], NULL, routine, &p.philos[i]))
            {
                free(p.philos);
                free(t);
                ft_error("cannot create a thread.");
            }
            pthread_mutex_lock(&p.check);
            p.philos[i].last_eat = p.s_time;
            pthread_mutex_unlock(&p.check);
            i++;
        }
        //usleep(3000);
        check_dead(&p);
        stop_simulation(&p, t);
    }
    else
        ft_error("Error : must to put at least 5 arguments.");
    return 0;
}
