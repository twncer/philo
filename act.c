/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:54:30 by btuncer           #+#    #+#             */
/*   Updated: 2025/08/28 01:17:43 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

void philo_act(t_philo *philo, char action)
{
    int id;

    id = philo->id;
    // if (philo->status == 'e')
    //     philo->ate_at = 10;
    philo->status = action;
    if (action == 'e')
        printf("philo %d is now eating.\n", id);
    else if (action == 's')
        printf("philo %d is now sleeping.\n", id);
    else if (action == 't')
        printf("philo %d is now thinking.\n", id);
}
