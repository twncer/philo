/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 08:32:07 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/08 18:49:29 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include "philo.h"

long long	current_time_ms(void)
{
	struct timeval	tval;

	gettimeofday(&tval, (void *)0);
	return ((long long)(tval.tv_sec) * 1000 + (tval.tv_usec) / 1000);
}

void zzz(int wait)
{
    long long target;
    t_dining *dining;

    target = current_time_ms() + wait;
    dining = get_dining(NULL);
    while (current_time_ms() < target)
    {
        pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
        if (!dining->running)
        {
            pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
            break;
        }
        pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
        usleep(100);
    }
}

long long timer(bool calibrate, bool fetch)
{
    static long long calibration = 0;

    pthread_mutex_lock(get_dining(NULL)->mutexes[MTX_TIMER]);
    if (calibrate)
    {
        calibration = current_time_ms();
        pthread_mutex_unlock(get_dining(NULL)->mutexes[MTX_TIMER]);
        return (current_time_ms() - calibration);
    }
    else if (fetch)
    {
        pthread_mutex_unlock(get_dining(NULL)->mutexes[MTX_TIMER]);
        return (current_time_ms() - calibration);
    }
    pthread_mutex_unlock(get_dining(NULL)->mutexes[MTX_TIMER]);
    return (-1);
}
