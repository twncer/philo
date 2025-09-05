/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 23:50:35 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/05 07:18:25 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./gc/gc.h"

void create_philos(t_dining *dining)
{
    int philo_count;
    t_philo *philo;
    t_philo *curr_philo;

    philo_count = dining->number_of_philos;
    while (philo_count--)
    {
        philo = new_philo();
        if (dining->first_philo == NULL)
        {
            dining->first_philo = philo;
            curr_philo = philo;
        }
        else
        {
            philo->fork_below = curr_philo->fork_above;
            curr_philo->next_philo = philo;
            curr_philo = curr_philo->next_philo;
            if (philo_count == 0)
                dining->first_philo->fork_below = curr_philo->fork_above;
        }
    }   
}

void set_mutexes(t_dining *dining)
{
    int fork_count;
    
    dining->mutexes = alloc(sizeof(pthread_mutex_t *) * 3);
    dining->mutexes[0] = new_mutex();
    dining->mutexes[1] = new_mutex();
    dining->mutexes[2] = new_mutex();
    dining->forks = alloc(sizeof(pthread_mutex_t) * dining->number_of_philos);
    fork_count = 0;
    while (fork_count < dining->number_of_philos)
    {
        pthread_mutex_init(&dining->forks[fork_count], NULL);
        fork_count++;
    }
}

t_dining *get_dining(t_dining *init)
{
    static t_dining *dining = NULL;

    if (init)
        dining = init;
    return (dining);
}

t_dining *serve(int argc, char **argv)
{
    t_dining *dining;

    dining = new_dining();
    // if (argc < 5 || argc > 6)
    //     return (NULL);
    // if (argc == 6)
    //     dining->optional_arg = true;
    dining->number_of_philos = 6;
    create_philos(dining);
    set_mutexes(dining);
    get_dining(dining);
    return (dining);
}

