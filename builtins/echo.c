/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:32:22 by jriga             #+#    #+#             */
/*   Updated: 2025/12/07 16:35:07 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fileft.h"
#include "libft.h"
#include "minishell.h"

int	handle_echo_command(t_command *cmd)
{
	int	i;
	int	newline;

	if (!cmd)
		return (1);
	i = 0;
	newline = 1;
	if (cmd->args[0] && !ft_strcmp(cmd->args[0], "-n"))
	{
		newline = 0;
		i = 1;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
