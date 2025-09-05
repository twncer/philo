/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 07:22:55 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/05 07:23:31 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    poke(false);
    while (checkered_flag(false) == false)
        ;
    if (philo->id % 2 == 0)
        zzz(10);
    
    pthread_exit(NULL);
}