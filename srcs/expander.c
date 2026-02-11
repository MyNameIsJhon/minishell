/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 21:36:31 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*find_end_var(char *var)
{
	while (*var)
	{
		if (!ft_isalnum(*var) && *var != '_')
			break ;
		var++;
	}
	return (var);
}

void	print_vars(char **vars)
{
	while (*vars)
	{
		printf("Var: %s\n", *vars);
		vars++;
	}
}

char	**recup_vars_in_token(t_token *token, t_arena *memory)
{
	char	**vars;
	char	*var;
	int		i;
	char	*end_var;

	vars = arena_alloc(memory, (ft_strcount_char(token->value, '$') + 1)
			* sizeof(char *), 8);
	i = 0;
	if (!vars)
		return (NULL);
	var = token->value;
	while (var)
	{
		var = ft_strchr(var, '$');
		if (!var)
			break ;
		end_var = find_end_var(var + 1);
		printf("Var found: %.*s\n", (int)(end_var - var), var);
		vars[i++] = ar_substr(var, 0, end_var - var, memory);
		var = end_var;
	}
	vars[i] = NULL;
	print_vars(vars);
	return (vars);
}

int	count_len_vars(char **vars)
{
	int	len;

	len = 0;
	while (*vars)
	{
		len += ft_strlen(*vars);
		vars++;
	}
	return (len);
}

int	count_len_expandeds(char **vars, t_env *env)
{
	int		len;
	t_env	*env_var;

	len = 0;
	while (*vars)
	{
		env_var = find_env(*vars + 1, env);
		if (env_var && env_var->value)
			len += ft_strlen(env_var->value);
		vars++;
	}
	return (len);
}

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

char	*join_token_var(t_token *token, t_context *ctx)
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
