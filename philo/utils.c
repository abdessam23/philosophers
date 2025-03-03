/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhimi <abhimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:17:06 by abhimi            #+#    #+#             */
/*   Updated: 2025/03/03 09:32:28 by abhimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t get_time()
{
    struct timeval t;
    gettimeofday(&t,NULL);
    return((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int ft_atoi(char *str)
{
    int i = 0;
    unsigned int result;

    result = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        i++;
    if(str[i] == '-')
        ft_error("Should enter a positive number as unsigned integer from 0 to INT_MAX");
    else if(str[i] == '+')
    {
        if (str[i + 1] == '\0')
            ft_error("Should enter a positive number as unsigned integer from 0 to INT_MAX");
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + str[i] - '0';
        if (result > INT_MAX)
            ft_error("Should enter number as unsigned integer from 0 to INT_MAX");
        i++;
    }
    if ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
        ft_error("Should enter only digits");
    return (result);
}
