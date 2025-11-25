/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 00:46:11 by jriga             #+#    #+#             */
/*   Updated: 2025/11/24 00:46:57 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"
#include <stdlib.h>

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
