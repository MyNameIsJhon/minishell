/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 21:46:34 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	copy_var_value(char *dest, int *z, char *var_name, t_context *ctx)
{
	t_env	*env_var;
	char	*val;

	if (var_name[0] == '?')
		val = ft_itoa(ctx->last_exit_status);
	else
	{
		env_var = find_env(var_name, ctx->env);
		if (!env_var || !env_var->value)
			return ;
		val = env_var->value;
	}
	while (*val)
		dest[(*z)++] = *val++;
}

static void	copy_with_expansion(char *new_value, char *curs, char **vars,
		t_context *ctx)
{
	int		i;
	int		y;
	int		z;

	i = 0;
	y = 0;
	z = 0;
	while (curs[i])
	{
		if (curs[i] == '$')
		{
			copy_var_value(new_value, &z, vars[y] + 1, ctx);
			i += ft_strlen(vars[y]);
			y++;
		}
		else
			new_value[z++] = curs[i++];
	}
	new_value[z] = '\0';
}

static char	*join_token_var(t_token *token, t_context *ctx)
{
	int		token_len;
	char	*new_value;
	char	**vars;

	vars = recup_vars_in_token(token, ctx->line_memory);
	token_len = ft_strlen(token->value) + count_len_expandeds(vars, ctx)
		- count_len_vars(vars) + 1;
	new_value = arena_alloc(ctx->line_memory, token_len * sizeof(char),
			sizeof(char));
	copy_with_expansion(new_value, token->value, vars, ctx);
	return (new_value);
}

static char	*expand_tilde(t_token *token, t_context *ctx)
{
	t_env	*home;

	home = find_env("HOME", ctx->env);
	if (!home || !home->value)
		return (token->value);
	if (token->value[1] == '\0' || token->value[1] == '/')
		return (ar_strjoin(ctx->line_memory, home->value, token->value + 1));
	return (token->value);
}


void	expand_tokens(t_tokenizer *tokenizer, t_context *ctx)
{
	t_token	*token;

	token = tokenizer->head;
	while (token)
	{
		if (!token->quote_type && token->value[0] == '~')
			token->value = expand_tilde(token, ctx);
		if (token->quote_type != '\'' && (ft_strchr(token->value, '$')))
			token->value = join_token_var(token, ctx);
		token = token->next;
	}
}
