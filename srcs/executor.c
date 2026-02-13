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

static int	handle_exit_status(int status)
{
	int	last_status;

	if (WIFEXITED(status))
		last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
	}
	else
		last_status = 1;
	return (last_status);
}

static void	child_process(t_command *cmd, char **envp, int *fd, t_context *ctx)
{
	set_sig(SIG_DFL);
	if (cmd->next && set_dup(fd[1], STDOUT_FILENO) == EXIT_FAILURE)
		exit(1);
	close(fd[0]);
	if (is_cmd_builtin(cmd) == true)
	{
		if (apply_redirections(cmd->redirections) < 0)
			exit(1);
		execute_builtin(cmd, ctx);
		exit(1);
	}	
	else
	{
		if (apply_redirections(cmd->redirections) < 0)
			exit(1);
		execve(cmd->exec_path, cmd->com_splited, envp);
	}
	exit(1);
}

static int	execute_loop(t_command *current, char **envp, pid_t *pid, t_context *ctx)
{
	if (pipe(current->fd) == -1)
		return (-1);
	set_sig(SIG_IGN);
	*pid = fork();
	if (*pid < 0)
	{
		close(current->fd[0]);
		close(current->fd[1]);
		return (-1);
	}
	if (!*pid)
		child_process(current, envp, current->fd, ctx);
	set_dup(current->fd[0], STDIN_FILENO);
	if (close(current->fd[1]) == -1)
		return (-1);
	return (0);
}

char	run_cmd(t_command *command, char **envp, t_context *ctx)
{
	pid_t		pid;
	pid_t		temp_pid;
	int			status[2];
	t_command	*current;
	int			save_std[2];

	status[1] = 127;
	current = command;
	save_std[0] = dup(STDIN_FILENO);
	save_std[1] = dup(STDOUT_FILENO);
	while (current)
	{
		execute_loop(current, envp, &pid, ctx);
		current = current->next;
	}
	while (1)
	{
		temp_pid = waitpid(-1, &status[0], 0);
		if (temp_pid == -1)
			break ;
		if (temp_pid == pid)
		{
			status[1] = handle_exit_status(status[0]);
			if (status[0] == 256)
				status[1] = 127;
		}
	}
	set_dup(save_std[0], STDIN_FILENO);
	set_dup(save_std[1], STDOUT_FILENO);
	return (status[1]);
}
/*char	run_cmd(t_command *command, char **envp, t_context *ctx)
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
		if (execute_loop(current, envp, &pid, ctx) == -1)
			return (-1);
		current = current->next;
	}
	waitpid(pid, &status, 0);
	set_dup(save_std[0], STDIN_FILENO);
	set_dup(save_std[1], STDOUT_FILENO);
	return (handle_exit_status(status));
}*/
