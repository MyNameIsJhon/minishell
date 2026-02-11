/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:18:47 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 21:26:33 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	remove_redir_tokens(t_token **tokens, t_token *prev, t_token *curr)
{
	if (prev)
		prev->next = curr->next->next;
	else
		*tokens = curr->next->next;
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
		if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				redir_add_back(&redirs, new_redir(current->type,
						current->next->value, memory));
				remove_redir_tokens(tokens, prev, current);
				current = current->next->next;
				continue ;
			}
		}
		prev = current;
		current = current->next;
	}
	return (redirs);
}

int	apply_redirections_with_backup(t_redir *redirs, int *saved_stdin,
		int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin < 0 || *saved_stdout < 0)
	{
		if (*saved_stdin >= 0)
			close(*saved_stdin);
		if (*saved_stdout >= 0)
			close(*saved_stdout);
		return (-1);
	}
	if (apply_redirections(redirs) < 0)
	{
		close(*saved_stdin);
		close(*saved_stdout);
		return (-1);
	}
	return (0);
}

void	restore_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
