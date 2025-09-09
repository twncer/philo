/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:21:17 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/09 10:37:41 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <stdio.h>
#include "gc.h"
#include "./../philo.h"

void *gc_exit()
{
    leave_();
    return (NULL);  
}

t_gc *get_gc()
{
    static t_gc *gc = NULL;

    if (!gc)
        gc = new_gc();
    if (!gc)
        return (gc_exit());
    return (gc);
}

void insert_to_gc(t_trash *new_trash)
{
    t_gc *gc;

    gc = get_gc();
    if (!gc->first_node)
    {
        gc->first_node = new_trash;
        gc->gc_mark = gc->first_node;
    }
    else
    {
        (gc->gc_mark)->next = new_trash;
        gc->gc_mark = (gc->gc_mark->next);
    }
}

void *alloc(ssize_t size)
{
    void *mem;
    t_trash *trash;
    
    mem = malloc(size);
    if (!mem)
        return (gc_exit());
    trash = new_trash(mem);
    if (!trash)
        return (gc_exit());
    insert_to_gc(trash);
    return (mem);
}

void dump_gc()
{
    t_trash *trash_node;
    t_trash *trash_node_swap;
    t_gc *gc;
       
    printf("--- cleaning ---\n");
    trash_node = get_gc()->first_node;
    while (trash_node)
    {
        if (trash_node->mem)
            free(trash_node->mem);
        trash_node_swap = trash_node->next;
        free(trash_node);
        trash_node = trash_node_swap;
    }
    gc = get_gc();
    if (gc)
        free(gc);
    printf("--- cleaning done ---\n");
}
