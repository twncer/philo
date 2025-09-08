/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:14:22 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/08 10:20:14 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

int check_eat_count(t_dining *dining)
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
            return (-1);
        }
        pthread_mutex_unlock(dining->mutexes[MTX_EAT_COUNT]);
    }
    return (eat_count);
}

void check_philos(t_dining *dining)
{
    t_philo *curr_philo;

    curr_philo = dining->first_philo;
    while (curr_philo)
    {
        check_philo(curr_philo);
        curr_philo = curr_philo->next_philo;
    }   
}

void *monitor_routine()
{
    t_dining *dining;

    poke(false);
    while (checkered_flag(false) == false)
        ;
    dining = get_dining(NULL);
    pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
    while (dining->running)
    {
        pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
        check_philos(dining);
        if (dining->optional_arg)
        {
            if (check_eat_count(dining) == dining->eat_count)
                leave_();
        }
        pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
    }
    pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
    return (NULL);
}