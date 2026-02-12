/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:02:04 by jriga             #+#    #+#             */
/*   Updated: 2025/12/07 16:44:27 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retval (int)
// command (t_command *)
// ctx (t_context *)

int	handle_builtins(t_command *command, t_context *ctx)
{
	int	retval;

	retval = 0;
	if (!ft_strcmp(command->com_splited[0], "cd"))
		retval = handle_cd_command(command, ctx);
	else if (!ft_strcmp(command->com_splited[0], "exit"))
		retval = handle_exit_command(command, ctx);
	else if (!ft_strcmp(command->com_splited[0], "env"))
		retval = print_env(ctx->env);
	else if (!ft_strcmp(command->com_splited[0], "unset"))
		retval = handle_unset_command(command, ctx);
	else if (!ft_strcmp(command->com_splited[0], "export"))
		retval = handle_export_command(command, ctx);
	else if (!ft_strcmp(command->com_splited[0], "echo"))
		retval = handle_echo_command(command);
	else if (!ft_strcmp(command->com_splited[0], "pwd"))
		retval = handle_pwd_command();
	return (retval);
}

int	execute_builtin(t_command *command, t_context *ctx)
{
	int	saved_stdin;
	int	saved_stdout;
	int	retval;

	if (command->redirections)
	{
		if (apply_redirections_with_backup(command->redirections, &saved_stdin,
				&saved_stdout) < 0)
			return (0);
	}
	retval = handle_builtins(command, ctx);
	if (command->redirections)
		restore_fds(saved_stdin, saved_stdout);
	return (retval);
}
