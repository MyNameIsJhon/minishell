/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:21:01 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 21:21:03 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}

static int	input_redir(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	output_redir(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	append_redir(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_IN && input_redir(redirs->file) < 0)
			return (-1);
		else if (redirs->type == TOKEN_REDIR_OUT
			&& output_redir(redirs->file) < 0)
			return (-1);
		else if (redirs->type == TOKEN_REDIR_APPEND
			&& append_redir(redirs->file) < 0)
			return (-1);
		else if (redirs->type == TOKEN_HEREDOC && heredoc(redirs->file) < 0)
			return (-1);
		redirs = redirs->next;
	}
	return (0);
}
