/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:26:33 by jriga             #+#    #+#             */
/*   Updated: 2025/11/25 03:59:09 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int	count_tokens(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static char	**tokens_to_array(t_token *tokens, t_arena *memory)
{
	int		count;
	char	**array;
	int		i;

	count = count_tokens(tokens);
	array = arena_alloc(memory, sizeof(char *) * (count + 1), 8);
	if (!array)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
		{
			array[i] = tokens->value;
			i++;
		}
		tokens = tokens->next;
	}
	array[i] = NULL;
	return (array);
}

static void	init_command_struct(t_command *cmd, char **split)
{
	cmd->com_splited = split;
	cmd->paths = NULL;
	cmd->exec_path = NULL;
	cmd->exec_maxlen = 0;
}

static t_token	*split_at_pipe(t_token **segment)
{
	t_token	*prev;
	t_token	*current;

	prev = NULL;
	current = *segment;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (prev)
				prev->next = NULL;
			else
				*segment = NULL;
			return (current->next);
		}
		prev = current;
		current = current->next;
	}
	return (NULL);
}

static t_command	*build_command(t_token *tokens, t_arena *memory)
{
	t_command	*cmd;

	cmd = arena_alloc(memory, sizeof(t_command), 8);
	if (!cmd)
		return (NULL);
	cmd->memory = memory;
	cmd->next = NULL;
	cmd->redirections = extract_redirections(&tokens, memory);
	cmd->com_splited = tokens_to_array(tokens, memory);
	if (!cmd->com_splited)
		return (NULL);
	init_command_struct(cmd, cmd->com_splited);
	return (cmd);
}

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
