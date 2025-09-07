/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 07:22:55 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/07 18:59:00 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int poke(bool fetch)
{
    static int poked = 0;
    int res;
    
    pthread_mutex_lock(get_dining(NULL)->mutexes[0]);
    if (fetch)
        res = poked;
    else
    {
        poked++;
        res = -1;
    }
    pthread_mutex_unlock(get_dining(NULL)->mutexes[0]);
    return (res);
}

bool checkered_flag(bool wave)
{
    static bool flag = false;
    bool res;

    pthread_mutex_lock(get_dining(NULL)->mutexes[1]);
    if (wave)
        flag = true;
    res = flag;
    pthread_mutex_unlock(get_dining(NULL)->mutexes[1]);
    return (res);
}

void leave_()
{
    get_dining(NULL)->running = false;
    // pthread_mutex_lock(get_dining(NULL)->mutexes[4]);
}

void check_philo(t_philo *philo)
{
    if (timer(false, true) >= get_dining(NULL)->time_to_die + philo->ate_at)
    {
        printf("%lld %d died\n", timer(false, true), philo->id);
        leave_();
    }
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    poke(false);
    while (checkered_flag(false) == false)
        ;
    if (philo->id % 2 == 0)
        zzz(10);
    while(get_dining(NULL)->running)
    {
        // pthread_mutex_lock(get_dining(NULL)->mutexes[6]);
        philo_act(philo, 'e');
        philo_act(philo, 's');
        philo_act(philo, 't');
        // pthread_mutex_unlock(get_dining(NULL)->mutexes[6]);
    }
    return (NULL);
}
