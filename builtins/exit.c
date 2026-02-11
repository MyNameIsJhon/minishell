/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 01:51:07 by jriga             #+#    #+#             */
/*   Updated: 2025/11/18 03:03:51 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit_command(t_command *command, t_context *ctx)
{
	if (!ft_strcmp(command->com_splited[0], "exit"))
	{
		context_free(&ctx);
		clear_history();
		exit(0);
	}
	return (0);
}
