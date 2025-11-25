/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 02:33:58 by jriga             #+#    #+#             */
/*   Updated: 2025/11/25 01:57:34 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_ALLOCATOR_H
# define ARENA_ALLOCATOR_H

# include <stddef.h>

typedef struct s_arena_block
{
	char					*data;
	size_t					offset;
	size_t					size;
	struct s_arena_block	*next;
}							t_arena_block;

typedef struct s_arena
{
	t_arena_block			*current;
	t_arena_block			*head;
	size_t					default_block_size;
}							t_arena;

size_t						align_up(size_t offset, size_t alignment);
t_arena_block				*create_block(size_t size);
t_arena						*arena_init(size_t size);
void						*arena_alloc(t_arena *a, size_t size,
								size_t alignment);
void						arena_free(t_arena *a);
void						arena_reset(t_arena *a);
char						**ar_split(const char *s, char c, t_arena *memory);
char						*ar_strdup(char *str, t_arena *memory);
char						*ar_strjoin(t_arena *arena, const char *s1,
								const char *s2);
char						*ar_substr(const char *s, unsigned int start,
								size_t len, t_arena *memory);

#endif
