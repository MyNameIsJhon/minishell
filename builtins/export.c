/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 03:36:47 by jriga             #+#    #+#             */
/*   Updated: 2025/11/21 04:49:01 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// check if last char of key = +
// find key
// alloc new str
void	print_export_env(t_context *ctx)//TODO is this the proper way to handle failure ?
{
	t_env	*env;

	env = ctx->env;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s=\"\"\n", env->name);
		env = env->next;
	}
}

static char	*ft_rm_pluschar(char *str, t_arena *global_mem)
{
	int		new_len;
	char	*new_str;

	new_len = ft_strlen(str) - 1;
	new_str = arena_alloc(global_mem, sizeof(char) * new_len + 1, 8);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, new_len + 1);
	return (new_str);
}

static char *write_append(char *ogval, char *apval, t_arena *global_mem)
{
	int		totlen;
	char	*new_val;
	int		ogval_len;

	ogval_len = ft_strlen(ogval);
	totlen = ogval_len + ft_strlen(apval);
	new_val = arena_alloc(global_mem, sizeof(char) * totlen + 1, 8);
	if (!new_val)
		return (NULL);
	if (ogval)
		ft_memcpy(new_val, ogval, ogval_len);
	ft_strlcpy(new_val + ogval_len, apval, ft_strlen(apval) + 1);
	return (new_val);
}

//TODO Securite sur empty old val, ou empty new val
int	handle_export_command(t_command *cmd, t_context *ctx)
{
	t_env	*env;
	char	**args;
	bool	is_append;

	is_append = false;
	if (!cmd || !ctx)
		return (0);
	args = ar_split(cmd->com_splited[1], '=', ctx->line_memory);
	if (!args)
		return (print_export_env(ctx), 0);
	if (args[0][ft_strlen(args[0]) - 1] == '+')
	{
		args[0] = ft_rm_pluschar(args[0], ctx->global_memory);
		if (!args[0])
			return (0);
		is_append = true;
	}
	env = find_env(args[0], ctx->env);
	if (!env)
	{
		env_add_back(new_env(args[0], args[1], ctx->global_memory), &ctx->env);
		return (1);
	}
	if (is_append == true)
		env->value = write_append(env->value, args[1], ctx->global_memory);
	if (is_append == false)
		env->value = ar_strdup(args[1], ctx->global_memory);
	return (1);
}
