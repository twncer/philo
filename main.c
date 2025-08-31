/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 05:41:25 by btuncer           #+#    #+#             */
/*   Updated: 2025/08/31 05:27:32 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include "constructors.h"

long long	current_time_ms(void);
void philo_act(t_philo *philo, char action);

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

int poke(bool fetch)
{
    static int poked = 0;
    
    if (fetch)
        return (poked);
    else
    {
        poked++;
        return (-1);
    }
}

long long timer(bool calibrate, bool fetch)
{
    static long long calibration = 0;

    if (calibrate)
    {
        calibration = current_time_ms();
        return (current_time_ms() - calibration);
    }
    else if (fetch)
        return (current_time_ms() - calibration);
    return (-1);
}

bool checkered_flag(bool wave)
{
    static bool flag = false;
    bool result;

    //lock mutex
    if (wave)
        flag = true;
    result = flag;
    //unlock mutext
    return (result);
}

bool checkered_flag(bool wave)
{
    static bool flag = false;

    if (wave)
        flag = true;
    return (flag);
}

t_dining *serve(int argc, char **argv)
{
    t_dining *dining;

    dining = new_dining();
    // if (argc < 5 || argc > 6)
    //     return (NULL);
    // if (argc == 6)
    //     dining->optional_arg = true;
    dining->number_of_philos = 100;
    create_philos(dining);
    return (dining);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    // printf("philo %d on duty!\n", philo->id);
    poke(false);
    while (checkered_flag(false) == false)
        usleep(1);
    while (philo->is_alive)
    {
        
    }
    philo_act(philo, 't');
    pthread_exit(NULL);
}

void slip(int wait)
{
    long long target = current_time_ms() + wait;
    while (current_time_ms() < target)
        usleep(100);
}

int main(int argc, char **argv)
{
    t_dining *dining;
    t_philo *curr_philo;
    pthread_t thread;

    dining = serve(argc, argv);
    curr_philo = dining->first_philo;
    while (curr_philo)
    {
        pthread_create(&thread, NULL, routine, curr_philo);
        curr_philo = curr_philo->next_philo;
    }
    while (poke(true) < dining->number_of_philos)
        usleep(1);
    printf("> sys: ready! poked %i times. timer at: %lld\n", poke(true), timer(true, true));
    timer(true, true);
    checkered_flag(true);
    usleep(10000000);
}

// int main(int argc, char **argv)
// {
//     int philo_count = 5;
//     t_dining *dining = new_dining();
//     t_philo *philo;
//     t_philo *curr_philo;

//     while (philo_count--)
//     {
//         philo = new_philo();
//         if (dining->first_philo == NULL)
//         {
//             dining->first_philo = philo;
//             curr_philo = philo;
//         }
//         else
//         {
//             philo->fork_below = curr_philo->fork_above;
//             curr_philo->next_philo = philo;
//             curr_philo = curr_philo->next_philo;
//             if (philo_count == 0)
//                 dining->first_philo->fork_below = curr_philo->fork_above;
//         }
//     }
//     return 0;
// }

// curr_philo = dining->first_philo;
// while (curr_philo)
// {
//     printf("fork %d < (philo %d) > fork %d\n", curr_philo->fork_below->id,
//                                                 curr_philo->id,
//                                                 curr_philo->fork_above->id); 
//     curr_philo = curr_philo->next_philo;
// }