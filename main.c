/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 05:41:25 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/08 14:32:39 by btuncer          ###   ########.fr       */
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
    pthread_join(*(get_dining(NULL)->monitor_thread), NULL);
    
    return (0);
}
