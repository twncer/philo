/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:30:16 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/09 18:36:37 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

void *alloc(ssize_t size);

pthread_t *new_thread()
{
    pthread_t *thread;

    thread = alloc(sizeof(pthread_t));
    return (thread);
}

t_philo *new_philo()
{
    t_philo *philo;
    static int id = 1;
    static int fork_id = 0;
    
    philo = alloc(sizeof(t_philo));

    philo->id = id;
    philo->status = 'T';
    philo->ate_at = 0;
    philo->eat_count = 0;
    philo->fork_above = fork_id;
    philo->is_alive = true;
    fork_id++;
    philo->fork_below = -1;
    philo->next_philo = NULL;
    philo->thread = new_thread();
    id++;
    return (philo);
}

t_dining *new_dining()
{
    t_dining *dining;

    dining = alloc(sizeof(t_dining));
    dining->optional_arg = false;
    
    dining->number_of_philos = 0;
    dining->time_to_die = 0;
    dining->time_to_eat = 0;
    dining->time_to_sleep = 0;
    dining->eat_count = 0;
    dining->first_philo = NULL;
    dining->mutexes = NULL;
    dining->running = true;
    dining->monitor_thread = new_thread();
    return (dining);
}

pthread_mutex_t *new_mutex()
{
    pthread_mutex_t *mutex;

    mutex = alloc(sizeof(pthread_mutex_t));
    if (pthread_mutex_init(mutex, NULL))
    {
        printf("err: pthread_mutex_init failed\n");
        leave_();
    }
    return (mutex);
}
