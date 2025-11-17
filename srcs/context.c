/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:00:00 by jriga             #+#    #+#             */
/*   Updated: 2025/11/17 00:00:00 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_context	*context_init(void)
{
	t_context	*ctx;

	ctx = malloc(sizeof(t_context));
	if (!ctx)
		return (NULL);
	ctx->global_memory = arena_init(4096);
	if (!ctx->global_memory)
	{
		free(ctx);
		return (NULL);
	}
	ctx->line_memory = arena_init(2048);
	if (!ctx->line_memory)
	{
		arena_free(ctx->global_memory);
		free(ctx);
		return (NULL);
	}
	ctx->env = NULL;
	ctx->user = "mynameisjhon";
	ctx->domain = "minishell";
	ctx->paths_maxlen = 0;
	return (ctx);
}

void	context_free(t_context **ctx)
{
	if (!ctx || !*ctx)
		return ;
	if ((*ctx)->global_memory)
		arena_free((*ctx)->global_memory);
	if ((*ctx)->line_memory)
		arena_free((*ctx)->line_memory);
	free(*ctx);
	*ctx = NULL;
}

void	context_reset_line(t_context *ctx)
{
	if (!ctx || !ctx->line_memory)
		return ;
	arena_reset(ctx->line_memory);
}
