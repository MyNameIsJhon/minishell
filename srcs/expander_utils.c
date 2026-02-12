/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:40:52 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 22:45:40 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_end_var(char *var)
{
	if (*var == '?')
		return (var + 1);
	while (*var)
	{
		if (!ft_isalnum(*var) && *var != '_')
			break ;
		var++;
	}
	return (var);
}

/* static void	print_vars(char **vars) */
/* { */
/* 	while (*vars) */
/* 	{ */
/* 		printf("Var: %s\n", *vars); */
/* 		vars++; */
/* 	} */
/* } */

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
		/* printf("Var found: %.*s\n", (int)(end_var - var), var); */
		vars[i++] = ar_substr(var, 0, end_var - var, memory);
		var = end_var;
	}
	vars[i] = NULL;
	/* print_vars(vars); */
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

int	count_len_expandeds(char **vars, t_context *ctx)
{
	int		len;
	t_env	*env_var;

	len = 0;
	while (*vars)
	{
		if ((*vars)[1] == '?')
			len += ft_strlen(ft_itoa(ctx->last_exit_status));
		else
		{
			env_var = find_env(*vars + 1, ctx->env);
			if (env_var && env_var->value)
				len += ft_strlen(env_var->value);
		}
		vars++;
	}
	return (len);
}
