/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:34:20 by jriga             #+#    #+#             */
/*   Updated: 2025/11/12 11:55:57 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"
#include <stdlib.h>
#include "libft.h"

t_arena	*arena_init(size_t size)
{
	t_arena *a;

	a = malloc(sizeof(t_arena));
	a->data = malloc(size);
	if (!a->data)
		return (NULL);
	a->size = size;
	a->offset = 0;
	return (a);
}

static size_t	align_up(size_t offset, size_t alignment)
{
	return ((offset + alignment - 1) & ~(alignment - 1));
}

void	arena_addmemory(t_arena *a, size_t new_size)
{
	char	*new_data;

	if (new_size <= a->size)
		return ;
	new_data = malloc(new_size);
	if (!new_data)
		return ;
	ft_memcpy(new_data, a->data, a->size);
	free(a->data);
	a->data = new_data;
	a->size = new_size;
}

void	*arena_alloc(t_arena *a, size_t size, size_t alignment)
{
	size_t	aligned;
	void	*new;

	aligned = align_up(a->offset, alignment);
	if (aligned + size > a->size)
	{
		size_t	new_size;

		new_size = a->size * 2;
		if (new_size < aligned + size)
			new_size = aligned + size;
		arena_addmemory(a, new_size);
		if (aligned + size > a->size)
			return (NULL);
	}
	new = a->data + aligned;
	a->offset = aligned + size;
	return (new);
}

void	arena_free(t_arena *a)
{
	free(a->data);
	free(a);
}
