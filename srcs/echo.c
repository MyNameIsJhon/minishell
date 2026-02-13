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

#include "minishell.h"

int	handle_echo_command(t_command *cmd)
{
	int	i;
	int	newline;

	if (!cmd)
		return (1);
	i = 1;
	newline = 1;
	if (cmd->com_splited[1] && !ft_strncmp(cmd->com_splited[1], "-n", 2))
	{
		newline = 0;
		i = 2;
	}
	while (cmd->com_splited[i])
	{
		ft_putstr_fd(cmd->com_splited[i], STDOUT_FILENO);
		if (cmd->com_splited[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
