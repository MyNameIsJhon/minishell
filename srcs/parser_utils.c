/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 22:14:47 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 22:44:10 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(t_token *tokens)
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

void	init_command_struct(t_command *cmd, char **split)
{
	cmd->com_splited = split;
	cmd->paths = NULL;
	cmd->exec_path = NULL;
	cmd->exec_maxlen = 0;
}

t_command	*build_command(t_token *tokens, t_arena *memory)
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

t_token	*split_at_pipe(t_token **segment)
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
