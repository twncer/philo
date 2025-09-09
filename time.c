/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 08:32:07 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/09 11:14:15 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

long long	current_time_ms(void)
{
	struct timeval	tval;

	gettimeofday(&tval, (void *)0);
	return ((long long)(tval.tv_sec) * 1000 + (tval.tv_usec) / 1000);
}

void	zzz(int wait)
{
	long long	target;
	t_dining	*dining;

	target = current_time_ms() + wait;
	dining = get_dining(NULL);
	while (current_time_ms() < target)
	{
		usleep(200);
	}
}

long long	timer(bool calibrate, bool fetch)
{
	static long long	calibration = 0;

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
