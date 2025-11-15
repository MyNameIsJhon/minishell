/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:26:33 by jriga             #+#    #+#             */
/*   Updated: 2025/11/15 01:25:45 by jriga            ###   ########.fr       */
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

void	free_splited_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

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

t_command	*mini_parser(char *user_input)
{
	char		**com_splited;
	int			l_com;
	t_command	*command;

	com_splited = ft_split(user_input, ' ');
	if (!com_splited)
		return (NULL);
	l_com = ft_strslen(com_splited);
	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
	{
		free_splited_array(com_splited);
		return (NULL);
	}
	init_command_struct(command, com_splited, l_com);
	return (command);
}

char	**get_executable_paths(char *env_path)
{
	char	**paths;
	char	*path;

	(void)env_path;
	/* if (!env_path) */
	/* 	return (NULL); */
	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (paths);
}

