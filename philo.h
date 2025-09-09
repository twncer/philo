/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:54:17 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/09 20:44:32 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>

# define MTX_POKE 0
# define MTX_CHECKERED 1
# define MTX_ALIVE 2
# define MTX_TIMER 3
# define MTX_PRINT 4
# define MTX_RUNNING 5
# define MTX_EAT_COUNT 6
# define MTX_ATE_AT 7

typedef struct s_philo t_philo;
typedef struct s_dining t_dining;
typedef struct s_fork t_fork;

struct s_philo
{
    int id;
    bool is_alive;
    char status;
    long long ate_at;
    int eat_count;
    
    int fork_above;
    int fork_below;
    
    t_philo *next_philo;
    pthread_t *thread;
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

    pthread_t *monitor_thread;
};

int	ft_atoi(const char *nptr);

t_dining *serve(int argc, char **argv);
t_dining *get_dining(t_dining *init);
int philo_act(t_philo *philo, char action);

long long	current_time_ms(void);
void zzz(int wait);
long long timer(bool calibrate, bool fetch);

t_philo *new_philo();
t_dining *new_dining();
pthread_mutex_t *new_mutex();

int poke(bool fetch);
bool checkered_flag(bool wave);
void *routine(void *arg);

void print_msg(int philo_id, char *msg);
int eat(t_philo *philo);
void philo_sleep(t_philo *philo);
void think(t_philo *philo);
t_philo *check_philo(t_philo *philo);

void leave_();
void *monitor_routine();
bool check_eat_count(t_dining *dining);

#endif