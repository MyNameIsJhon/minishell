/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 00:00:00 by jriga             #+#    #+#             */
/*   Updated: 2026/02/09 00:36:02 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

char	*get_hostname(t_arena *memory)
{
	int		fd;
	char	*hostname;
	char	buf[1024];
	int		len;

	fd = open("/proc/sys/kernel/hostname", O_RDONLY);
	if (fd < 0)
		return (NULL);
	len = read(fd, buf, 1023);
	close(fd);
	if (len < 0)
		return (NULL);
	if (len > 0 && buf[len - 1] == '\n')
		len--;
	buf[len] = '\0';
	hostname = ar_strdup(buf, memory);
	return (hostname);
}

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
	ctx->user = getenv("USER");
	ctx->hostname = get_hostname(ctx->global_memory);
	ctx->paths_maxlen = 0;
	ctx->last_exit_status = 0;
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
