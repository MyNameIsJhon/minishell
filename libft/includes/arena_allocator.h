/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:33:58 by jriga             #+#    #+#             */
/*   Updated: 2025/11/18 00:52:26 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_ALLOCATOR_H
# define ARENA_ALLOCATOR_H

# include <stddef.h>

typedef struct s_arena_block
{
	char				*data;
	size_t				offset;
	size_t				size;
	struct s_arena_block	*next;
}				t_arena_block;

typedef struct s_arena
{
	t_arena_block	*current;
	t_arena_block	*head;
	size_t			default_block_size;
}				t_arena;

t_arena	*arena_init(size_t size);
void	*arena_alloc(t_arena *a, size_t size, size_t alignment);
void	arena_free(t_arena *a);
void	arena_reset(t_arena *a);
char	**ar_split(const char *s, char c, t_arena *memory);
char	*ar_strdup(char *str, t_arena *memory);

#endif
