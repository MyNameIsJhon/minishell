/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 01:24:47 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 21:34:00 by jriga            ###   ########.fr       */
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
	if (apply_redirections(cmd->redirections) < 0)
		exit(1);
	execve(cmd->exec_path, cmd->com_splited, envp);
	dprintf(2, "\nexec_path: %s\n", cmd->exec_path);
	exit(1);
}

static int	execute_loop(t_command *current, char **envp, pid_t *pid)
{
	if (pipe(current->fd) == -1)
		return (-1);
	*pid = fork();
	if (*pid < 0)
	{
		close(current->fd[0]);
		close(current->fd[1]);
		return (-1);
	}
	if (!*pid)
		child_process(current, envp, current->fd);
	set_dup(current->fd[0], STDIN_FILENO);
	if (close(current->fd[1]) == -1)
		return (-1);
	return (0);
}

char	run_cmd(t_command *command, char **envp)
{
	pid_t		pid;
	int			status;
	t_command	*current;
	int			save_std[2];

	current = command;
	save_std[0] = dup(STDIN_FILENO);
	save_std[1] = dup(STDOUT_FILENO);
	while (current)
	{
		if (execute_loop(current, envp, &pid) == -1)
			return (-1);
		current = current->next;
	}
	waitpid(pid, &status, 0);
	set_dup(save_std[0], STDIN_FILENO);
	set_dup(save_std[1], STDOUT_FILENO);
	return (WEXITSTATUS(status));
}
