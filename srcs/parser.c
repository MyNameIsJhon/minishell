/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:26:33 by jriga             #+#    #+#             */
/*   Updated: 2025/11/12 15:42:54 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/dir.h>

t_command	*mini_parser(char *user_input)
{
	char		**com_splited;
	int			l_com;
	t_command	*command;

	com_splited = ft_split(user_input, ' ');
	l_com = ft_strslen(com_splited);
	command = (t_command *)malloc(sizeof(t_command));
	if (l_com >= 1)
	{
		command->program = com_splited[0];
		command->args = com_splited + 1;
		command->com_splited = com_splited;
	}
	return (command);
}

void	command_free(t_command **command)
{
	ft_strsfree((*command)->com_splited);
	free(*command);
}
char **get_executable_paths(char *env_path) {
	char **paths;
	char *path;
	(void)env_path;


	/* if (!env_path) */
	/* 	return (NULL); */
	path = getenv("PATH");
	paths = ft_split(path, ':');
	return (paths);
}

int	exec_prog(t_command *command)
{
	int				i;
	DIR				*dir;
	struct dirent	*s_dir;

	i = 0;
	command->paths = get_executable_paths(NULL);
	command->exec_maxlen = find_max_len(command->paths) + EXEC_MAXLEN;
	command->exec_path = malloc(command->exec_maxlen * sizeof(char));
	while (command->paths[i])
	{
		if (access(command->paths[i], X_OK))
		{
			i++;
			continue ;
		}
		dir = opendir(command->paths[i]);
		s_dir = readdir(dir);
		while (s_dir)
		{
			if (ft_strcmp(s_dir->d_name, command->program))
			{
				s_dir = readdir(dir);
				continue ;
			}
			ft_strlcpy(command->exec_path, s_dir->d_name, command->exec_maxlen);
			ft_strlcat(command->exec_path, s_dir->d_name, command->exec_maxlen);
			execve(command->exec_path, command->args, NULL);
			ft_bzero((void *)command->exec_path, command->exec_maxlen);
			s_dir = readdir(dir);
			return 0;
		}
		i++;
		closedir(dir);
	}
	return 1;
}

void command_print(t_command *command)
{
	int i;

	if (!command)
		return;
	printf("Program: %s\n", command->program);
	printf("Arguments:\n");
	for (i = 0; command->args[i]; i++)
		printf("  %s\n", command->args[i]);
	printf("Splitted Command:\n");
	for (i = 0; command->com_splited[i]; i++)
		printf("  %s\n", command->com_splited[i]);
}
