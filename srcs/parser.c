/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:26:33 by jriga             #+#    #+#             */
/*   Updated: 2025/11/15 01:40:57 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void	init_command_struct(t_command *cmd, char **split, int len)
{
	cmd->com_splited = split;
	cmd->paths = NULL;
	cmd->exec_path = NULL;
	cmd->exec_maxlen = 0;
	if (len >= 1)
	{
		cmd->program = split[0];
		cmd->args = split + 1;
	}
	else
	{
		cmd->program = NULL;
		cmd->args = NULL;
	}
}

t_command	*mini_parser(char *user_input, t_context *ctx)
{
	t_command	*command;
	int			l_com;

	if (!ctx || !ctx->line_memory)
		return (NULL);
	command = arena_alloc(ctx->line_memory, sizeof(t_command), 8);
	if (!command)
		return (NULL);
	command->memory = ctx->line_memory;
	command->com_splited = ar_split(user_input, ' ', command->memory);
	if (!command->com_splited)
		return (NULL);
	l_com = ft_strslen(command->com_splited);
	init_command_struct(command, command->com_splited, l_com);
	return (command);
}

char	**get_executable_paths(t_command *cmd)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	return (ar_split(path, ':', cmd->memory));
}
