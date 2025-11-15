/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 01:24:47 by jriga             #+#    #+#             */
/*   Updated: 2025/11/15 03:55:40 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void	command_free(t_command **command)
{
	if (!command || !*command)
		return ;
	if ((*command)->com_splited)
		free_splited_array((*command)->com_splited);
	if ((*command)->paths)
		free_splited_array((*command)->paths);
	if ((*command)->exec_path)
		free((*command)->exec_path);
	free(*command);
	*command = NULL;
}

static void	child_process(t_command *cmd, char **envp, int *fd)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == (-1))
	{
		close(fd[1]);
		exit(1);
	}
	close(fd[1]);
	execve(cmd->exec_path, cmd->com_splited, envp);
	exit(1);
}

static void	read_output(int fd_read)
{
	char	buffer[1024];
	ssize_t	n;

	while ((n = read(fd_read, buffer, sizeof(buffer))) > 0)
	{
		if (write(STDOUT_FILENO, buffer, n) == (-1))
		{
			close(fd_read);
			break ;
		}
	}
}

int	run_cmd(t_command *command, char **envp)
{
	int		fd[2];
	pid_t	pid;
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
		child_process(command, envp, fd);
	close(fd[1]);
	read_output(fd[0]);
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
