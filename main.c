/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 05:41:25 by btuncer           #+#    #+#             */
/*   Updated: 2025/08/28 08:39:13 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <pthread.h>
#include "constructors.h"

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

t_dining *serve(int argc, char **argv)
{
    t_dining *dining;

    dining = new_dining();
    // if (argc < 5 || argc > 6)
    //     return (NULL);
    // if (argc == 6)
    //     dining->optional_arg = true;

    dining->number_of_philos = 500;
    create_philos(dining);
    return (dining);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    printf("philo %d on duty!\n", philo->id);
    pthread_exit(NULL);
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
    usleep(5000000);
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