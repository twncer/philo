/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cons.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:37:42 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/03 20:19:17 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_gc *new_gc()
{
    t_gc *gc;

    gc = malloc(sizeof(t_gc));
    if (!gc)
        return (NULL);
    gc->first_node = NULL;
    gc->gc_mark = NULL;
    return (gc);
}

t_trash *new_trash(void *mem)
{
    t_trash *trash;

    trash = malloc(sizeof(t_trash));
    if (!trash)
        return (NULL);
    trash->mem = mem;
    trash->next = NULL;
    return (trash);
}
