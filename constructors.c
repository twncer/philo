/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:30:16 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/03 21:40:02 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

void *alloc(ssize_t size);

t_fork *new_fork()
{
    t_fork *fork;
    static int id = 1;

    fork = (t_fork *)alloc(sizeof(t_fork));
    if (!fork)
        exit(1);
    fork->id = id;
    fork->taken = false;
    id++;
    return (fork);
}

t_philo *new_philo()
{
    t_philo *philo;
    static int id = 1;

    philo = alloc(sizeof(t_philo));

    philo->id = id;
    philo->forks_held = false;
    philo->status = 'T';
    philo->fork_above = new_fork();
    philo->fork_below = NULL;
    philo->next_philo = NULL;
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
    return (dining);
}

pthread_mutex_t *new_mutex()
{
    pthread_mutex_t *mutex;

    mutex = alloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    return (mutex);
}
