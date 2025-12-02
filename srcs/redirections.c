/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:40:53 by jriga             #+#    #+#             */
/*   Updated: 2025/12/02 22:47:03 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "fileft.h"

static int	handle_input_redir(char *file)
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

static int	handle_output_redir(char *file)
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

static int	handle_append_redir(char *file)
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
		if (redirs->type == TOKEN_REDIR_IN)
		{
			if (handle_input_redir(redirs->file) < 0)
				return (-1);
		}
		else if (redirs->type == TOKEN_REDIR_OUT)
		{
			if (handle_output_redir(redirs->file) < 0)
				return (-1);
		}
		else if (redirs->type == TOKEN_REDIR_APPEND)
		{
			if (handle_append_redir(redirs->file) < 0)
				return (-1);
		}
		redirs = redirs->next;
	}
	return (0);
}

t_redir	*new_redir(t_token_type type, char *file, t_arena *memory)
{
	t_redir	*redir;

	redir = arena_alloc(memory, sizeof(t_redir), 8);
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

void	redir_add_back(t_redir **head, t_redir *new)
{
	t_redir	*current;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

t_redir	*extract_redirections(t_token **tokens, t_arena *memory)
{
	t_redir	*redirs;
	t_token	*current;
	t_token	*prev;

	redirs = NULL;
	current = *tokens;
	prev = NULL;
	while (current)
	{
		if (current->type >= TOKEN_REDIR_IN
			&& current->type <= TOKEN_HEREDOC)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				redir_add_back(&redirs, new_redir(current->type,
						current->next->value, memory));
				if (prev)
					prev->next = current->next->next;
				else
					*tokens = current->next->next;
				current = current->next->next;
				continue ;
			}
		}
		prev = current;
		current = current->next;
	}
	return (redirs);
}
