/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 07:22:55 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/09 14:53:19 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	poke(bool fetch)
{
	static int	poked = 0;
	int			res;

	pthread_mutex_lock(get_dining(NULL)->mutexes[MTX_POKE]);
	if (fetch)
		res = poked;
	else
	{
		poked++;
		res = -1;
	}
	pthread_mutex_unlock(get_dining(NULL)->mutexes[MTX_POKE]);
	return (res);
}

bool	checkered_flag(bool wave)
{
	static bool	flag = false;
	bool		res;

	pthread_mutex_lock(get_dining(NULL)->mutexes[MTX_CHECKERED]);
	if (wave)
		flag = true;
	res = flag;
	pthread_mutex_unlock(get_dining(NULL)->mutexes[MTX_CHECKERED]);
	return (res);
}

void	leave_(void)
{
	t_dining	*dining;

	dining = get_dining(NULL);
	pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
	get_dining(NULL)->running = false;
	pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
}

t_philo	*check_philo(t_philo *philo)
{
	t_dining	*dining;

	dining = get_dining(NULL);
	pthread_mutex_lock(dining->mutexes[MTX_ATE_AT]);
	if (timer(false, true) >= dining->time_to_die + philo->ate_at)
	{
		pthread_mutex_unlock(dining->mutexes[MTX_ATE_AT]);
		pthread_mutex_lock(dining->mutexes[MTX_PRINT]);
		philo->is_alive = false;
		philo->ate_at = timer(false, true);
		leave_();
		return (philo);
	}
	pthread_mutex_unlock(dining->mutexes[MTX_ATE_AT]);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_dining	*dining;

	philo = (t_philo *)arg;
	dining = get_dining(NULL);
	poke(false);
	while (checkered_flag(false) == false)
		;
	if (philo->id % 2 == 0)
		zzz(10);
	while (1)
	{
		pthread_mutex_lock(dining->mutexes[MTX_RUNNING]);
		if (!get_dining(NULL)->running)
		{
			pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
			break;
		}
		pthread_mutex_unlock(dining->mutexes[MTX_RUNNING]);
		if (philo_act(philo, 'e') == 200)
			break;
		philo_act(philo, 's');
		philo_act(philo, 't');
	}
	return (NULL);
}
