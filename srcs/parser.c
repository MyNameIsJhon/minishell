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
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

t_command	*mini_parser(char *user_input)
{
	char		**com_splited;
	int			l_com;
	t_command	*command;
	int			i;

	com_splited = ft_split(user_input, ' ');
	if (!com_splited)
		return (NULL);
	l_com = ft_strslen(com_splited);
	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
	{
		i = 0;
		while (com_splited[i])
			free(com_splited[i++]);
		free(com_splited);
		return (NULL);
	}
	command->com_splited = com_splited;
	command->paths = NULL;
	command->exec_path = NULL;
	command->exec_maxlen = 0;
	if (l_com >= 1)
	{
		command->program = com_splited[0];
		command->args = com_splited + 1;
	}
	else
	{
		command->program = NULL;
		command->args = NULL;
	}
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

char	*find_prog(t_command *command)
{
	int				i;
	DIR				*dir;
	struct dirent	*s_dir;
	int				n;

	i = 0;
	command->paths = get_executable_paths(NULL);
	if (!command->paths)
		return (NULL);
	command->exec_maxlen = find_max_len(command->paths) + EXEC_MAXLEN;
	command->exec_path = malloc(command->exec_maxlen * sizeof(char));
	if (!command->exec_path)
		return (NULL);
	while (command->paths[i])
	{
		if (access(command->paths[i], X_OK))
		{
			i++;
			continue ;
		}
		dir = opendir(command->paths[i]);
		if (!dir)
		{
			i++;
			continue ;
		}
		s_dir = readdir(dir);
		while (s_dir)
		{
			if (ft_strcmp(s_dir->d_name, command->program))
			{
				s_dir = readdir(dir);
				continue ;
			}
			n = ft_strlcpy(command->exec_path, command->paths[i],
					command->exec_maxlen);
			command->exec_path[n] = '/';
			command->exec_path[n + 1] = '\0';
			ft_strlcat(command->exec_path, s_dir->d_name, command->exec_maxlen);
			closedir(dir);
			return (command->exec_path);
			/* ft_bzero((void *)command->exec_path, command->exec_maxlen); */
			/* s_dir = readdir(dir); */
			/* return (0); */
		}
		i++;
		closedir(dir);
	}
	return (NULL);
}

void	command_free(t_command **command)
{
	int	i;

	if (!command || !*command)
		return ;
	if ((*command)->com_splited)
	{
		i = 0;
		while ((*command)->com_splited[i])
		{
			free((*command)->com_splited[i]);
			i++;
		}
		free((*command)->com_splited);
	}
	if ((*command)->paths)
	{
		i = 0;
		while ((*command)->paths[i])
		{
			free((*command)->paths[i]);
			i++;
		}
		free((*command)->paths);
	}
	if ((*command)->exec_path)
		free((*command)->exec_path);
	free(*command);
	*command = NULL;
}

int	run_cmd(t_command *command, char **envp)
{
	int		fd[2];
	pid_t	pid;
	char	buffer[1024];
	ssize_t	n;
	int		status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (!pid)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == (-1))
		{
			close(fd[1]);
			exit(1);
		}
		close(fd[1]);
		execve(command->exec_path, command->com_splited, envp);
		exit(1);
	}
	close(fd[1]);
	while ((n = read(fd[0], buffer, sizeof(buffer))) > 0)
	{
		if (write(STDOUT_FILENO, buffer, n) == (-1))
		{
			close(fd[0]);
			break ;
		}
	}
	close(fd[0]);
	waitpid(pid, &status, 0);
	return (0);
}

void	command_print(t_command *command)
{
	int	i;

	if (!command)
		return ;
	printf("Program: %s\n", command->program);
	printf("Arguments:\n");
	for (i = 0; command->args[i]; i++)
		printf("  %s\n", command->args[i]);
	printf("Splitted Command:\n");
	for (i = 0; command->com_splited[i]; i++)
		printf("  %s\n", command->com_splited[i]);
}
