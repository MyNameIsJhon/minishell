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

#include "minishell.h"

static void	add_token_internal(t_tokenizer *tok, t_token_type type, char *value,
		char quote_type)
{
	t_token	*new;

	new = arena_alloc(tok->memory, sizeof(t_token), 8);
	if (!new)
		return ;
	*new = (t_token){type, value, quote_type, NULL};
	if (!tok->head)
		tok->head = new;
	else
		tok->tail->next = new;
	tok->tail = new;
}

void	add_token(t_tokenizer *tok, t_token_type type, char *value)
{
	add_token_internal(tok, type, value, 0);
}

int	extract_quoted(char *input, int i, t_tokenizer *tok)
{
	char	quote;
	int		start;
	int		j;
	char	*value;

	quote = input[i++];
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] != quote)
	{
		ft_putstr_fd("Error: unclosed quote\n", 2);
		return (i);
	}
	j = i - start;
	value = arena_alloc(tok->memory, j + 1, 1);
	if (!value)
		return (i + 1);
	ft_memcpy(value, &input[start], j);
	value[j] = '\0';
	add_token_internal(tok, TOKEN_WORD, value, quote);
	return (i + 1);
}

int	extract_word(char *input, int i, t_tokenizer *tok)
{
	int		start;
	int		len;
	char	*value;

	start = i;
	while (input[i] && !is_separator(input[i]))
		i++;
	len = i - start;
	value = arena_alloc(tok->memory, len + 1, 1);
	if (!value)
		return (i);
	ft_memcpy(value, &input[start], len);
	value[len] = '\0';
	add_token(tok, TOKEN_WORD, value);
	return (i);
}
