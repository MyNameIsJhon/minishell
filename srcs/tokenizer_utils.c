/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:31:34 by jriga             #+#    #+#             */
/*   Updated: 2025/11/17 20:34:58 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

int	is_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>'
		|| c == '\'' || c == '"');
}

void	add_token(t_token **head, t_token **tail, t_token_type type,
		char *value, t_arena *memory)
{
	t_token	*new;

	new = arena_alloc(memory, sizeof(t_token), 8);
	if (!new)
		return ;
	new->type = type;
	new->value = value;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

int	extract_quoted(char *input, int i, t_token **head, t_token **tail,
		t_arena *memory)
{
	char	quote;
	int		start;
	int		j;
	char	*value;
	int		k;

	quote = input[i];
	start = i + 1;
	j = start;
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] != quote)
	{
		write(2, "Error: unclosed quote\n", 22);
		return (j);
	}
	value = arena_alloc(memory, j - start + 1, 1);
	if (!value)
		return (j + 1);
	k = 0;
	while (k < j - start)
	{
		value[k] = input[start + k];
		k++;
	}
	value[k] = '\0';
	add_token(head, tail, TOKEN_WORD, value, memory);
	return (j + 1);
}

int	extract_word(char *input, int i, t_token **head, t_token **tail,
		t_arena *memory)
{
	int		start;
	int		len;
	char	*value;
	int		j;

	start = i;
	while (input[i] && !is_separator(input[i]))
		i++;
	len = i - start;
	value = arena_alloc(memory, len + 1, 1);
	if (!value)
		return (i);
	j = 0;
	while (j < len)
	{
		value[j] = input[start + j];
		j++;
	}
	value[j] = '\0';
	add_token(head, tail, TOKEN_WORD, value, memory);
	return (i);
}

int	handle_operator(char *input, int i, t_token **head, t_token **tail,
		t_arena *memory)
{
	if (input[i] == '|')
	{
		add_token(head, tail, TOKEN_PIPE, "|", memory);
		return (i + 1);
	}
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		add_token(head, tail, TOKEN_HEREDOC, "<<", memory);
		return (i + 2);
	}
	else if (input[i] == '>' && input[i + 1] == '>')
	{
		add_token(head, tail, TOKEN_REDIR_APPEND, ">>", memory);
		return (i + 2);
	}
	else if (input[i] == '<')
	{
		add_token(head, tail, TOKEN_REDIR_IN, "<", memory);
		return (i + 1);
	}
	else if (input[i] == '>')
	{
		add_token(head, tail, TOKEN_REDIR_OUT, ">", memory);
		return (i + 1);
	}
	return (i);
}
