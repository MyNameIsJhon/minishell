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

static void	init_command_struct(t_command *cmd, char **split, int len)
{
	cmd->com_splited = split;
	cmd->paths = NULL;
	cmd->exec_path = NULL;
	cmd->exec_maxlen = 0;
	if (len >= 1)
	{
		cmd->program = split[0];
		cmd->args = split + 1;
	}
	else
	{
		cmd->program = NULL;
		cmd->args = NULL;
	}
}

void	print_token_list(t_token *tokens)
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
	t_command	*command;
	t_token		*tokens;
	t_tokenizer	tokenizer;
	int			l_com;

	if (!ctx || !ctx->line_memory)
		return (NULL);
	command = arena_alloc(ctx->line_memory, sizeof(t_command), 8);
	if (!command)
		return (NULL);
	command->memory = ctx->line_memory;
	tokens = tokenize(user_input, command->memory);
	tokenizer.head = tokens;
	tokenizer.memory = command->memory;
	expand_tokens(&tokenizer, ctx);
	command->tokens = tokens;
	command->com_splited = tokens_to_array(tokens, command->memory);
	if (!command->com_splited)
		return (NULL);
	l_com = ft_strslen(command->com_splited);
	init_command_struct(command, command->com_splited, l_com);
	return (command);
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
