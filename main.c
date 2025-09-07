/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 05:41:25 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/07 18:53:17 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "philo.h"
#include "./gc/gc.h"

__attribute__((destructor))
void cya()
{
    dump_gc();
}

int check_eat_count(t_dining *dining)
{
    t_philo *curr_philo;
    int eat_count;

    curr_philo = dining->first_philo;
    eat_count = curr_philo->eat_count;
    while (curr_philo)
    {
        curr_philo = curr_philo->next_philo;
        if (curr_philo && curr_philo->eat_count != eat_count)
            return -1;
    }
    return (eat_count);
}

void *monitor_routine()
{
    t_philo *curr_philo;
    t_dining *dining;

    poke(false);
    while (checkered_flag(false) == false)
        ;
    dining = get_dining(NULL);
    while (dining->running)
    {
        curr_philo = dining->first_philo;
        while (curr_philo)
        {
            check_philo(curr_philo);
            curr_philo = curr_philo->next_philo;
        }
        if (dining->optional_arg)
        {
            if (check_eat_count(dining) == dining->eat_count)
                leave_();
        }
    }
    return (NULL);
}

int main(int argc, char **argv)
{
    t_philo *curr_philo;
    
    serve(argc, argv);
    
    curr_philo = get_dining(NULL)->first_philo;
    while (curr_philo)
    {
        pthread_create(curr_philo->thread, NULL, routine, curr_philo);
        curr_philo = curr_philo->next_philo;
    }
    pthread_create(get_dining(NULL)->monitor_thread, NULL, monitor_routine, NULL);

    while (poke(true) < get_dining(NULL)->number_of_philos + 1)
        usleep(1);

    timer(true, true);
    checkered_flag(true);

    curr_philo = get_dining(NULL)->first_philo;
    while (curr_philo)
    {
        pthread_join(*(curr_philo->thread), NULL);
        curr_philo = curr_philo->next_philo;
    }
    return (0);
}
