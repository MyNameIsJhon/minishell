/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 01:37:20 by jriga             #+#    #+#             */
/*   Updated: 2025/11/21 03:04:59 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>

int	handle_unset_command(t_command *cmd, t_context *ctx)
{
	if (!cmd || !ctx)
		return (1);
	env_delete(cmd->com_splited[1], &ctx->env);
	return (0);
}
