/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 01:21:35 by jriga             #+#    #+#             */
/*   Updated: 2025/11/15 01:23:42 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>

static char	*build_exec_path(t_command *cmd, char *path_dir, char *prog_name)
{
	int	n;

	n = ft_strlcpy(cmd->exec_path, path_dir, cmd->exec_maxlen);
	cmd->exec_path[n] = '/';
	cmd->exec_path[n + 1] = '\0';
	ft_strlcat(cmd->exec_path, prog_name, cmd->exec_maxlen);
	return (cmd->exec_path);
}

static char	*search_in_dir(t_command *cmd, DIR *dir, int path_idx)
{
	struct dirent	*s_dir;

	s_dir = readdir(dir);
	while (s_dir)
	{
		if (ft_strcmp(s_dir->d_name, cmd->program))
		{
			s_dir = readdir(dir);
			continue ;
		}
		return (build_exec_path(cmd, cmd->paths[path_idx], s_dir->d_name));
	}
	return (NULL);
}

static int	init_prog_search(t_command *command)
{
	int	i;

	command->paths = get_executable_paths(NULL);
	if (!command->paths)
		return (0);
	command->exec_maxlen = find_max_len(command->paths) + EXEC_MAXLEN;
	command->exec_path = malloc(command->exec_maxlen * sizeof(char));
	if (!command->exec_path)
	{
		i = 0;
		while (command->paths[i])
			free(command->paths[i++]);
		free(command->paths);
		command->paths = NULL;
		return (0);
	}
	return (1);
}

static char	*check_path_dir(t_command *cmd, int i)
{
	DIR		*dir;
	char	*result;

	if (access(cmd->paths[i], X_OK))
		return (NULL);
	dir = opendir(cmd->paths[i]);
	if (!dir)
		return (NULL);
	result = search_in_dir(cmd, dir, i);
	closedir(dir);
	return (result);
}

char	*find_prog(t_command *command)
{
	int		i;
	char	*result;

	if (!init_prog_search(command))
		return (NULL);
	i = 0;
	while (command->paths[i])
	{
		result = check_path_dir(command, i);
		if (result)
			return (result);
		i++;
	}
	return (NULL);
}
