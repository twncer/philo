/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 23:50:35 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/09 18:34:53 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./gc/gc.h"
#include <stdio.h>

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
    
    dining->mutexes = alloc(sizeof(pthread_mutex_t *) * 8);
    dining->mutexes[0] = new_mutex();
    dining->mutexes[1] = new_mutex();
    dining->mutexes[2] = new_mutex();
    dining->mutexes[3] = new_mutex();
    dining->mutexes[4] = new_mutex();
    dining->mutexes[5] = new_mutex();
    dining->mutexes[6] = new_mutex();
    dining->mutexes[7] = new_mutex();
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

bool is_args_valid(t_dining *d)
{
    if (d->number_of_philos < 1 || d->time_to_die < 1
        || d->time_to_eat < 1 || d->time_to_sleep < 1)
        return (printf("err: Arguments should be greater than 0\n"), false);
    if (d->optional_arg && d->eat_count < 1)
        return (printf("err: Arguments should be greater than 0\n"), false);
    return (true);
}

t_dining *serve(int argc, char **argv)
{
    t_dining *dining;

    dining = new_dining();
    if (argc < 5 || argc > 6)
        return (printf("err: 4 or 5 arguments only.\n"), NULL);
    if (argc == 6)
    {
        dining->optional_arg = true;
        dining->eat_count = ft_atoi(argv[5]);
    }
    else
        dining->optional_arg = false;
    dining->number_of_philos = ft_atoi(argv[1]);
    dining->time_to_die = ft_atoi(argv[2]);
    dining->time_to_eat = ft_atoi(argv[3]);
    dining->time_to_sleep = ft_atoi(argv[4]);
    if (!is_args_valid(dining))
        return (NULL);
    create_philos(dining);
    set_mutexes(dining);
    get_dining(dining);
    return (dining);
}
