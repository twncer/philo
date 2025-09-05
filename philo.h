/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:54:17 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/05 07:23:20 by btuncer          ###   ########.fr       */
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
    pthread_t *thread;

    int fork_above;
    int fork_below;

    t_philo *next_philo;
};

struct s_dining
{
    bool optional_arg;
    int number_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat_count;
    bool running;
    t_philo *first_philo;
    pthread_mutex_t **mutexes;
    pthread_mutex_t *forks;
};

t_dining *get_dining(t_dining *init);
t_dining *serve(int argc, char **argv);
long long	current_time_ms(void);
void zzz(int wait);
long long timer(bool calibrate, bool fetch);
t_philo *new_philo();
t_dining *new_dining();
pthread_mutex_t *new_mutex();
void *routine(void *arg);

#endif