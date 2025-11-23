/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 00:00:12 by jriga             #+#    #+#             */
/*   Updated: 2025/11/17 20:32:28 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	handle_operator(char *input, int i, t_tokenizer *tok)
{
	if (input[i] == '|')
		return (add_token(tok, TOKEN_PIPE, "|"), i + 1);
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (add_token(tok, TOKEN_HEREDOC, "<<"), i + 2);
		return (add_token(tok, TOKEN_REDIR_IN, "<"), i + 1);
	}
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (add_token(tok, TOKEN_REDIR_APPEND, ">>"), i + 2);
		return (add_token(tok, TOKEN_REDIR_OUT, ">"), i + 1);
	}
	return (i);
}

int	is_separator(char c)
{
	return (ft_strchr(SEPARATORS, c) != NULL);
}

int	is_operator(char c)
{
	return (ft_strchr(OPERATORS, c) != NULL);
}

int	is_quote(char c)
{
	return (ft_strchr(QUOTES, c) != NULL);
}

t_token	*tokenize(char *input, t_arena *memory)
{
	t_tokenizer	tok;
	int			i;

	tok = (t_tokenizer){NULL, NULL, memory};
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_strchr(" \t", input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_quote(input[i]))
			i = extract_quoted(input, i, &tok);
		else if (is_operator(input[i]))
			i = handle_operator(input, i, &tok);
		else
			i = extract_word(input, i, &tok);
	}
	return (tok.head);
}
