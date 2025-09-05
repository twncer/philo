/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:54:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/05 06:54:52 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

long long	current_time_ms(void);
long long timer(bool calibrate, bool fetch);

void philo_act(t_philo *philo, char action)
{
    int id;

    pthread_mutex_lock(get_dining(NULL)->mutexes[2]);
    if (!get_dining(NULL)->running)
    {
        pthread_mutex_unlock(get_dining(NULL)->mutexes[2]);
        return ;
    }
    id = philo->id;
    // if (philo->status == 'e')
    //     philo->ate_at = 10;
    philo->status = action;
    if (action == 'e')
        printf("%lld %d is eating\n", timer(false, true), id);
    else if (action == 's')
        printf("%lld %d is sleeping\n", timer(false, true), id);
    else if (action == 't')
        printf("%lld %d is thinking\n", timer(false, true), id);
    else if (action == 'f')
        printf("%lld %d has taken a fork\n", timer(false, true), id);
    else if (action == 'd')
        printf("%lld %d died\n", timer(true, false), id);
    pthread_mutex_unlock(get_dining(NULL)->mutexes[2]);
}
