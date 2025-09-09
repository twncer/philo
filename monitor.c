/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:14:22 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/09 14:57:50 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "philo.h"

bool check_eat_count(t_dining *dining)
{
    t_philo *curr_philo;
    int eat_count;

    curr_philo = dining->first_philo;
    pthread_mutex_lock(dining->mutexes[MTX_EAT_COUNT]);
    eat_count = curr_philo->eat_count;
    pthread_mutex_unlock(dining->mutexes[MTX_EAT_COUNT]);
    while (curr_philo)
    {
        curr_philo = curr_philo->next_philo;
        pthread_mutex_lock(dining->mutexes[MTX_EAT_COUNT]);
        if (curr_philo && curr_philo->eat_count != eat_count)
        {
            pthread_mutex_unlock(dining->mutexes[MTX_EAT_COUNT]);
            return (false);
        }
        pthread_mutex_unlock(dining->mutexes[MTX_EAT_COUNT]);
    }
    return (eat_count == dining->eat_count);
}

t_philo *check_all_philos(t_dining *dining)
{
    t_philo *curr_philo;
    t_philo *philo;
    
    curr_philo = dining->first_philo;
    while (curr_philo)
    {
        philo = check_philo(curr_philo);
        if (philo)
            return (philo);
        curr_philo = curr_philo->next_philo;
    }
    return (NULL);
}

void *monitor_routine()
{
    t_dining *dining;
    t_philo *philo;
    
    poke(false);
    while (checkered_flag(false) == false)
        ;
    dining = get_dining(NULL);
    pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
    while (dining->running)
    {
        pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
        philo = check_all_philos(dining);
        if (philo)
        {
            pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
            break;
        }
        if (dining->optional_arg && check_eat_count(dining))
        {
            pthread_mutex_lock(dining->mutexes[MTX_PRINT]);
            leave_();
            pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
            philo = NULL;
            break ;
        }
        pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
    }
    pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
    pthread_mutex_unlock(dining->mutexes[MTX_PRINT]);
    if (philo)
    {
        pthread_mutex_lock(dining->mutexes[MTX_ATE_AT]);
        printf("%lld %d died\n", philo->ate_at, philo->id);
        pthread_mutex_unlock(dining->mutexes[MTX_ATE_AT]);
    }
    return (NULL);
}
