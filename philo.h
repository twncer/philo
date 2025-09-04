/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:54:17 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/03 20:40:16 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo t_philo;
typedef struct s_dining t_dining;
typedef struct s_fork t_fork;

struct s_philo
{
    int id;
    bool is_alive;
    bool right_hand;
    bool left_hand;   // iki eli tutmaya gerek olmayabilir, çünkü
                      // zaten 2 fork almadan asla yemeyecek. sadece
                      // ikisi de müsaitse alabilecek. o durumda:
    bool forks_held;  // <- daha mantikli olabilir.
    char status;
    long long ate_at;
    int eat_count;
    t_fork *fork_above;
    t_fork *fork_below;
    t_philo *next_philo;
};

struct s_fork
{
    int id;
    bool taken;
};

struct s_dining
{
    bool optional_arg;
    int number_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_count;
    t_philo *first_philo;
    pthread_mutex_t *mutexes;
};

#endif