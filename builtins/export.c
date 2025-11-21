/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 03:36:47 by jriga             #+#    #+#             */
/*   Updated: 2025/11/21 04:08:11 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"
#include "libft.h"
#include "minishell.h"

int	handle_export_command(t_command *cmd, t_context *ctx)
{
	t_env	*env;
	char	**args;

	if (!cmd || !ctx)
		return (0);
	args = ar_split(cmd->args[0], '=', ctx->line_memory);
	env = find_env(cmd->args[0], ctx->env);
	if (env)
	{
		env->value = ar_strdup(args[0], ctx->global_memory);
		return (1);
	}
	env_add_back(new_env(args[0], args[1], ctx->global_memory), &ctx->env);
	return (1);
}
