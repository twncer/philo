/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:27:36 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/03 21:39:59 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_trash t_trash;
typedef struct s_gc t_gc;

struct s_trash
{
    void *mem;
    t_trash *next;
};

struct s_gc
{
    t_trash *first_node;
    t_trash *gc_mark;
};

t_gc *new_gc();
t_trash *new_trash(void *mem);
void *alloc(ssize_t size);
void dump_gc();
