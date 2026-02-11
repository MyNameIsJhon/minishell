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
	if (set_dup(fd[0], STDIN_FILENO) == EXIT_FAILURE)
		exit(1);
	if (cmd->next && set_dup(fd[1], STDOUT_FILENO) == EXIT_FAILURE)
		exit(1);
	printf("sin:%d - sout:%d\n", STDIN_FILENO, STDOUT_FILENO);
	if (apply_redirections(cmd->redirections) < 0)
		exit(1);
	execve(cmd->exec_path, cmd->com_splited, envp);
	exit(1);//TODO Proper error statuses
}

/*static void	read_output(int fd_read)
{
	char	buffer[1024];
	ssize_t	n;

	n = read(fd_read, buffer, sizeof(buffer));
	while (n > 0)
	{
		if (write(STDOUT_FILENO, buffer, n) == (-1))
		{
			close(fd_read);
			break ;
		}
		n = read(fd_read, buffer, sizeof(buffer));
	}
}*/

/*
 * - Creer pipe if not end
 * - Create fork
 * - Dup2 fd
 *	- If pipe is start : fd in = stdin or fd from file, if pipe is last, stdout or file
 * - Close after duping, child because dup full programm in parent and execve exit and protec fail
 * - Then execve
 * - fd d'un fichier ?
 * - wait pid after all process over, outside of loop
 * - handle signals in child process -> man waitpid for variable ?
 */

//static void	pipe_line()
//{

//}

int	run_cmd(t_command *command, char **envp)
{
	int			fd[2];
	pid_t		pid;
	int			status;
	t_command	*current;
	int			prev_fd;

	current = command;
	prev_fd = STDIN_FILENO;
	printf("Passed by run_cmd\n");
	while (current)
	{
		if (current->next && pipe(fd) == -1)
			return (-1);
		if (!current->next)//TODO can be cleaner than this
			fd[1] = STDOUT_FILENO;
		printf("prev_fd:%d\n", prev_fd);
		fd[0] = prev_fd;
		printf("fd0:%d - fd1:%d\n", fd[0], fd[1]);
		pid = fork();
		if (pid < 0)
			return (close(fd[0]), close(fd[1]), -1);
		if (!pid)
			child_process(current, envp, fd);
		if (current->next && close(fd[1]) == -1)
			return (-1);
		if (current->next && prev_fd != STDIN_FILENO && close(prev_fd) == -1)
			return (-1);
		prev_fd = fd[1];
		current = current->next;
	}
	waitpid(pid, &status, 0);
	return (0);
}

//read_output(fd[0]);//TODO Read of pipe is bad, what is the purpose, save the previous result
//
/* void	command_print(t_command *command) */
/* { */
/* 	int	i; */
/**/
/* 	if (!command) */
/* 		return ; */
/* 	printf("Program: %s\n", command->program); */
/* 	printf("Arguments:\n"); */
/* 	for (i = 0; command->args[i]; i++) */
/* 		printf("  %s\n", command->args[i]); */
/* 	printf("Splitted Command:\n"); */
/* 	for (i = 0; command->com_splited[i]; i++) */
/* 		printf("  %s\n", command->com_splited[i]); */
/* } */
