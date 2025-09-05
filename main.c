/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 05:41:25 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/05 07:21:36 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "philo.h"
#include "./gc/gc.h"

long long	current_time_ms(void);
void philo_act(t_philo *philo, char action);

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

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // printf("philo %d on duty!\n", philo->id);
    poke(false);
    while (checkered_flag(false) == false)
        ;
    if (philo->id % 2 == 0)
        zzz(10);
    philo_act(philo, 't');
    pthread_exit(NULL);
}

__attribute__((destructor))
void cya()
{
    printf("cya!\n");
    dump_gc();
}

int main(int argc, char **argv)
{
    t_dining *dining;
    t_philo *curr_philo;
    
    serve(argc, argv);

    curr_philo = get_dining(NULL)->first_philo;
    while (curr_philo)
    {
        printf("%d < PHILO%d > %d\n", curr_philo->fork_below, curr_philo->id, curr_philo->fork_above);
        curr_philo = curr_philo->next_philo;
    }
    return 0;

    curr_philo = get_dining(NULL)->first_philo;
    while (curr_philo)
    {
        pthread_create(curr_philo->thread, NULL, routine, curr_philo);
        curr_philo = curr_philo->next_philo;
    }

    while (poke(true) < get_dining(NULL)->number_of_philos)
        usleep(1);

    printf("> sys: ready! poked %i times. timer at: %lld\n", poke(true), timer(true, true));
    timer(true, true);
    checkered_flag(true);

    usleep(5000000);
    
    curr_philo = get_dining(NULL)->first_philo;
    while (curr_philo)
    {
        pthread_join(*(curr_philo->thread), NULL);
        curr_philo = curr_philo->next_philo;
    }
    
    exit(0);
}
