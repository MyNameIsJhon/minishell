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

static int	ft_isarray_onlydigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static long	handle_arg_toobig(long arg)
{
	int	nbr;
	
	if (arg < -256)
		nbr = 256;
	else if (arg > 256)
		nbr = -256;
	while (arg > 256 || arg < -256)
		arg += nbr;
	return (arg);
}

int	handle_exit_command(t_command *command, t_context *ctx)
{
	long	arg;

	arg = 0;
	if (command->com_splited[1] && ft_isarray_onlydigit(command->com_splited[1]) == EXIT_FAILURE)
	{
		context_free(&ctx);
		clear_history();
		ft_puterror("exit\n");
		ft_puterror("exit: ");
		ft_puterror(command->com_splited[1]);
		ft_puterror(": numeric argument required\n");
		exit(2);
	}
	if (command->com_splited[1] && command->com_splited[2])//TODO must have exit num 1
	{
		ft_puterror("exit\n");
		ft_puterror("exit: too many arguments\n");
		return (0);
	}
	if (command->com_splited[1])
	{
		arg = ft_atol(command->com_splited[1]);
		if (arg > 256 || arg < - 256)
			handle_arg_toobig(arg);
	}
	if (!ft_strcmp(command->com_splited[0], "exit"))//TODO Does this security makes any sense ?
	{
		context_free(&ctx);
		clear_history();
		ft_puterror("exit\n");
		exit(arg);
	}
	return (0);
}
