/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 08:32:07 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/07 18:12:37 by btuncer          ###   ########.fr       */
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

    target = current_time_ms() + wait;
    while (current_time_ms() < target)
        usleep(100);
}

long long timer(bool calibrate, bool fetch)
{
    static long long calibration = 0;

    pthread_mutex_lock(get_dining(NULL)->mutexes[3]);
    if (calibrate)
    {
        calibration = current_time_ms();
        pthread_mutex_unlock(get_dining(NULL)->mutexes[3]);
        return (current_time_ms() - calibration);
    }
    else if (fetch)
    {
        pthread_mutex_unlock(get_dining(NULL)->mutexes[3]);
        return (current_time_ms() - calibration);
    }
    pthread_mutex_unlock(get_dining(NULL)->mutexes[3]);
    return (-1);
}