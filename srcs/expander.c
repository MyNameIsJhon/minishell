/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 00:00:00 by jriga             #+#    #+#             */
/*   Updated: 2025/11/23 00:00:00 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_var_char(char c, int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static int	get_var_name_len(char *str)
{
	int	len;

	len = 0;
	if (!is_valid_var_char(str[len], 1))
		return (0);
	len++;
	while (str[len] && is_valid_var_char(str[len], 0))
		len++;
	return (len);
}

static char	*get_var_value(char *var_name, int len, t_context *ctx)
{
	t_env	*env_var;
	char	*name;

	name = arena_alloc(ctx->line_memory, len + 1, 1);
	if (!name)
		return ("");
	ft_strlcpy(name, var_name, len + 1);
	env_var = find_env(name, ctx->env);
	if (!env_var || !env_var->value)
		return ("");
	return (env_var->value);
}

static char	*get_exit_status(t_context *ctx)
{
	char	*status;

	status = ft_itoa(ctx->last_exit_status);
	if (!status)
		return ("0");
	return (status);
}

static int	calculate_expanded_len(char *str, t_context *ctx)
{
	int	len;
	int	i;
	int	var_len;
	char	*value;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				len += ft_strlen(get_exit_status(ctx));
				i += 2;
			}
			else if ((var_len = get_var_name_len(&str[i + 1])) > 0)
			{
				value = get_var_value(&str[i + 1], var_len, ctx);
				len += ft_strlen(value);
				i += var_len + 1;
			}
			else
			{
				len++;
				i++;
			}
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	append_string(char **dest, char *src, int *pos)
{
	int	i;

	i = 0;
	while (src[i])
	{
		(*dest)[*pos] = src[i];
		(*pos)++;
		i++;
	}
}

char	*expand_variables(char *str, t_context *ctx)
{
	char	*result;
	int		i;
	int		pos;
	int		var_len;
	char	*value;

	if (!str)
		return (str);
	result = arena_alloc(ctx->line_memory, calculate_expanded_len(str, ctx) + 1, 1);
	if (!result)
		return (str);
	i = 0;
	pos = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			if (str[i + 1] == '?')
			{
				value = get_exit_status(ctx);
				append_string(&result, value, &pos);
				i += 2;
			}
			else if ((var_len = get_var_name_len(&str[i + 1])) > 0)
			{
				value = get_var_value(&str[i + 1], var_len, ctx);
				append_string(&result, value, &pos);
				i += var_len + 1;
			}
			else
			{
				result[pos++] = str[i++];
			}
		}
		else
		{
			result[pos++] = str[i++];
		}
	}
	result[pos] = '\0';
	return (result);
}

void	expand_tokens(t_token *tokens, t_context *ctx)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD && tokens->quote_type != '\'')
		{
			tokens->value = expand_variables(tokens->value, ctx);
		}
		tokens = tokens->next;
	}
}
