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

static void	copy_env_value(char *new_value, int *z, t_env *env_var)
{
	int	val_len;

	val_len = 0;
	while (env_var->value[val_len])
		new_value[(*z)++] = env_var->value[val_len++];
}

static void	copy_with_expansion(char *new_value, char *curs, char **vars,
		t_env *env)
{
	int		i;
	int		y;
	int		z;
	t_env	*env_var;

	i = 0;
	y = 0;
	z = 0;
	while (curs[i])
	{
		if (curs[i] == '$')
		{
			env_var = find_env(vars[y] + 1, env);
			if (env_var && env_var->value)
				copy_env_value(new_value, &z, env_var);
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
	token_len = ft_strlen(token->value) + count_len_expandeds(vars, ctx->env)
		- count_len_vars(vars) + 1;
	new_value = arena_alloc(ctx->line_memory, token_len * sizeof(char),
			sizeof(char));
	copy_with_expansion(new_value, token->value, vars, ctx->env);
	return (new_value);
}

void	expand_tokens(t_tokenizer *tokenizer, t_context *ctx)
{
	t_token	*token;

	token = tokenizer->head;
	while (token)
	{
		if (token->quote_type != '\'' && (ft_strchr(token->value, '$')))
			token->value = join_token_var(token, ctx);
		token = token->next;
	}
}
