/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:26:33 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 22:21:42 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token Type: %d, Value: %s, Quotes type: %c\n", current->type,
			current->value, current->quote_type);
		current = current->next;
	}
}

t_command	*mini_parser(char *user_input, t_context *ctx)
{
	t_token		*tokens;
	t_tokenizer	tokenizer;
	t_command	*cmds;
	t_command	**tail;
	t_token		*rest;

	if (!ctx || !ctx->line_memory)
		return (NULL);
	tokens = tokenize(user_input, ctx->line_memory);
	tokenizer.head = tokens;
	tokenizer.memory = ctx->line_memory;
	expand_tokens(&tokenizer, ctx);
	cmds = NULL;
	tail = &cmds;
	while (tokens)
	{
		rest = split_at_pipe(&tokens);
		*tail = build_command(tokens, ctx->line_memory);
		if (!*tail)
			return (NULL);
		tail = &(*tail)->next;
		tokens = rest;
	}
	return (cmds);
}

char	**get_executable_paths(t_command *cmd, t_context *ctx)
{
	char	*path;
	t_env	*env;

	env = find_env("PATH", ctx->env);
	if (!env || !env->value)
		return (NULL);
	path = env->value;
	return (ar_split(path, ':', cmd->memory));
}
