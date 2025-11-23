/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 02:27:37 by jriga             #+#    #+#             */
/*   Updated: 2025/11/23 02:33:58 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fileft.h"
#include "libft.h"
#include "minishell.h"
#include <unistd.h>

int	handle_cd_command(t_command *command, t_context *ctx)
{
	t_env	*home;

	if (!command->args[0])
	{
		home = find_env("HOME", ctx->env);
		if (!home || !home->value)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		chdir(home->value);
		return (0);
	}
	chdir(command->args[0]);
	return (0);
}
