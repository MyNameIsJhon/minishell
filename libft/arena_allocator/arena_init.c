/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:34:20 by jriga             #+#    #+#             */
/*   Updated: 2025/11/24 00:51:42 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"
#include "libft.h"
#include <stdlib.h>

size_t	align_up(size_t offset, size_t alignment)
{
	return ((offset + alignment - 1) & ~(alignment - 1));
}

t_arena_block	*create_block(size_t size)
{
	t_arena_block	*block;

	block = ft_calloc(sizeof(t_arena_block), 1);
	if (!block)
		return (NULL);
	block->data = ft_calloc(size, 1);
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

	a = ft_calloc(sizeof(t_arena), 1);
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
