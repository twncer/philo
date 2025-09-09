/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 05:41:25 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/09 20:44:20 by btuncer          ###   ########.fr       */
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

void thread_err_case()
{
    t_dining *dining;

    dining = get_dining(NULL);
    pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
    dining->running = false;
    pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
    printf("err: pthread_create failed\n");
}

int main(int argc, char **argv)
{
    t_philo *curr_philo;
    bool err;

    err = false;
    if (!serve(argc, argv))
        return (1);    
    curr_philo = get_dining(NULL)->first_philo;
    while (curr_philo)
    {
        if (pthread_create(curr_philo->thread, NULL, routine, curr_philo))
        {
            err = true;
            curr_philo->thread = NULL;
            thread_err_case();
            break;
        }
        curr_philo = curr_philo->next_philo;
    }
    if (!err && pthread_create(get_dining(NULL)->monitor_thread, NULL, monitor_routine, NULL))
        thread_err_case();

    if (err == false)
        while (poke(true) < get_dining(NULL)->number_of_philos + 1)
            usleep(1);
    
    
    timer(true, true);
    checkered_flag(true);

    curr_philo = get_dining(NULL)->first_philo;
    while (curr_philo)
    {
        if (!curr_philo->thread)
            break;
        if (curr_philo && curr_philo->thread)
            pthread_join(*(curr_philo->thread), NULL);
        curr_philo = curr_philo->next_philo;
    }
    if (!err)
        pthread_join(*(get_dining(NULL)->monitor_thread), NULL);
    
    return (0);
}
