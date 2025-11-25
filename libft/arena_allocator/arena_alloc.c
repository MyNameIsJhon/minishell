/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:47:49 by jriga             #+#    #+#             */
/*   Updated: 2025/11/24 00:48:12 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"

static int	add_new_block(t_arena *a, size_t needed_size)
{
	t_arena_block	*new_block;
	t_arena_block	*last;
	size_t			block_size;

	if (a->current->next && a->current->next->size >= needed_size)
	{
		a->current = a->current->next;
		return (1);
	}
	if (needed_size > a->default_block_size)
		block_size = needed_size;
	else
		block_size = a->default_block_size;
	new_block = create_block(block_size);
	if (!new_block)
		return (0);
	last = a->current;
	while (last->next)
		last = last->next;
	last->next = new_block;
	a->current = new_block;
	return (1);
}

void	*arena_alloc(t_arena *a, size_t size, size_t alignment)
{
	size_t	aligned;
	void	*ptr;

	if (!a || !a->current)
		return (NULL);
	aligned = align_up(a->current->offset, alignment);
	if (aligned + size > a->current->size)
	{
		if (!add_new_block(a, aligned + size))
			return (NULL);
		aligned = 0;
	}
	ptr = a->current->data + aligned;
	a->current->offset = aligned + size;
	return (ptr);
}

