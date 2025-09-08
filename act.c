/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:54:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/08 19:27:18 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

void print_msg(int philo_id, char *msg)
{
    t_dining *dining;

    dining = get_dining(NULL);
    pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
    if (dining->running)
    {
        pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
        pthread_mutex_lock(dining->mutexes[MTX_PRINT]);
        printf("%lld %d %s\n", timer(false, true), philo_id, msg);
        pthread_mutex_unlock(dining->mutexes[MTX_PRINT]);
        return ;
    }
    pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
}

void take_forks(t_philo *philo)
{
    t_dining *dining;

    dining = get_dining(NULL);
    if (!(philo->id % 2 == 0))
    {
        pthread_mutex_lock(&(dining->forks[philo->fork_below]));
        print_msg(philo->id, "has taken a fork");
        pthread_mutex_lock(&(dining->forks[philo->fork_above]));
        print_msg(philo->id, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&(dining->forks[philo->fork_above]));
        print_msg(philo->id, "has taken a fork");
        pthread_mutex_lock(&(dining->forks[philo->fork_below]));
        print_msg(philo->id, "has taken a fork");
    }
}

void release_forks(t_philo *philo)
{
    t_dining *dining;

    dining = get_dining(NULL);
    if (!(philo->id % 2 == 0))
    {
        pthread_mutex_unlock(&(dining->forks[philo->fork_above]));
        pthread_mutex_unlock(&(dining->forks[philo->fork_below]));
    }
    else
    {
        pthread_mutex_unlock(&(dining->forks[philo->fork_below]));
        pthread_mutex_unlock(&(dining->forks[philo->fork_above]));
    }
}

void eat(t_philo *philo)
{
    t_dining *dining;
    
    dining = get_dining(NULL);
    check_philo(philo);
    take_forks(philo);
    check_philo(philo); 

    pthread_mutex_lock(dining->mutexes[MTX_ATE_AT]);
    philo->ate_at = timer(false, true);
    pthread_mutex_unlock(dining->mutexes[MTX_ATE_AT]);
    
    print_msg(philo->id, "is eating");
    
    zzz(get_dining(NULL)->time_to_eat);

    pthread_mutex_lock(dining->mutexes[MTX_EAT_COUNT]);
    philo->eat_count++;
    pthread_mutex_unlock(dining->mutexes[MTX_EAT_COUNT]);
    
    release_forks(philo);
}

void philo_sleep(t_philo *philo)
{
    print_msg(philo->id, "is sleeping");
    zzz(get_dining(NULL)->time_to_sleep);
}

void think(t_philo *philo)
{
    t_dining *dining;

    dining = get_dining(NULL);
    print_msg(philo->id, "is thinking");
    zzz((dining->time_to_die - (dining->time_to_eat + dining->time_to_sleep)) / 2);
}

void philo_act(t_philo *philo, char action)
{
    t_dining *dining;

    dining = get_dining(NULL);
    if (action == 'e')
        eat(philo);
    else if (action == 's')
        philo_sleep(philo);
    else if (action == 't')
        think(philo);
}

// int id;
// pthread_mutex_lock(dining->mutexes[MTX_ACT]);
// id = philo->id;
// if (!dining->running)
// {
//     pthread_mutex_unlock(get_dining(NULL)->mutexes[MTX_ACT]);
    // return ;
// }
// pthread_mutex_unlock(get_dining(NULL)->mutexes[MTX_ACT]);