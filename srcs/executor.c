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

static int	set_dup(int fd, int stream)
{
	if (fd == stream)
		return (EXIT_SUCCESS);
	if (dup2(fd, stream) == (-1))
		return (close(fd), EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

static void	child_process(t_command *cmd, char **envp, int *fd)
{
	if (cmd->next && set_dup(fd[1], STDOUT_FILENO) == EXIT_FAILURE)
		exit(1);
	close(fd[0]);
	//dprintf(2, "sin:%d - sout:%d\n", fd[0], fd[1]);
	if (apply_redirections(cmd->redirections) < 0)
		exit(1);
	execve(cmd->exec_path, cmd->com_splited, envp);
	dprintf(2, "\nexex_path: %s\n", cmd->exec_path);
	exit(1);//TODO Proper error statuses
}


int	run_cmd(t_command *command, char **envp)
{
	pid_t		pid;
	int			status;
	t_command	*current;
	int			save_std[2];

	current = command;
	save_std[0] = dup(STDIN_FILENO);
	save_std[1] = dup(STDOUT_FILENO);
	//printf("\nPassed by run_cmd\n");
	while (current)
	{
		if (pipe(current->fd) == -1)
			return (-1);
		//dprintf(2, "current->fd0:%d - current->fd1:%d\n", current->fd[0], current->fd[1]);
		//dprintf(2, "stdin:%d - stdout:%d\n", STDIN_FILENO, STDOUT_FILENO);
		pid = fork();
		if (pid < 0)
			return (close(current->fd[0]), close(current->fd[1]), -1);
		if (!pid)
			child_process(current, envp, current->fd);
		set_dup(current->fd[0], STDIN_FILENO);
		if (close(current->fd[1]) == -1)
			return (-1);
		current = current->next;
	}
	waitpid(pid, &status, 0);
	//dprintf(2, "sstd0:%d - sstd1:%d\n", save_std[0], save_std[1]);
	set_dup(save_std[0], STDIN_FILENO);
	set_dup(save_std[1], STDOUT_FILENO);
	//dprintf(2, "current->fd0:%d - current->fd1:%d\n", STDIN_FILENO, STDOUT_FILENO);
	return (0);
}
