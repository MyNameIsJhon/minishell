/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:34:20 by jriga             #+#    #+#             */
/*   Updated: 2025/11/17 00:00:00 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"
#include <stdlib.h>

static size_t	align_up(size_t offset, size_t alignment)
{
	return ((offset + alignment - 1) & ~(alignment - 1));
}

static t_arena_block	*create_block(size_t size)
{
	t_arena_block	*block;

	block = malloc(sizeof(t_arena_block));
	if (!block)
		return (NULL);
	block->data = malloc(size);
	if (!block->data)
	{
		free(block);
		return (NULL);
	}
	block->size = size;
	block->offset = 0;
	block->next = NULL;
	return (block);
}

t_arena	*arena_init(size_t size)
{
	t_arena	*a;

	a = malloc(sizeof(t_arena));
	if (!a)
		return (NULL);
	a->head = create_block(size);
	if (!a->head)
	{
		free(a);
		return (NULL);
	}
	a->current = a->head;
	a->default_block_size = size;
	return (a);
}

static int	add_new_block(t_arena *a, size_t needed_size)
{
	t_arena_block	*new_block;
	size_t			block_size;

	if (needed_size > a->default_block_size)
		block_size = needed_size;
	else
		block_size = a->default_block_size;
	new_block = create_block(block_size);
	if (!new_block)
		return (0);
	a->current->next = new_block;
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

void	arena_free(t_arena *a)
{
	t_arena_block	*current;
	t_arena_block	*next;

	if (!a)
		return ;
	current = a->head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	free(a);
}

void	arena_reset(t_arena *a)
{
	t_arena_block	*block;

	if (!a)
		return ;
	block = a->head;
	while (block)
	{
		block->offset = 0;
		block = block->next;
	}
	a->current = a->head;
}
