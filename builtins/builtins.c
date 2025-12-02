/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:02:04 by jriga             #+#    #+#             */
/*   Updated: 2025/12/03 00:03:08 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	execute_builtin(t_command *command, t_context *ctx)
{
	int	saved_stdin;
	int	saved_stdout;

	if (command->redirections)
	{
		if (apply_redirections_with_backup(command->redirections, &saved_stdin,
				&saved_stdout) < 0)
			return (0);
	}
	if (!ft_strcmp(command->program, "cd"))
		handle_cd_command(command, ctx);
	else if (!ft_strcmp(command->program, "exit"))
		handle_exit_command(command, ctx);
	else if (!ft_strcmp(command->program, "env"))
		print_env(ctx->env);
	else if (!ft_strcmp(command->program, "unset"))
		handle_unset_command(command, ctx);
	else if (!ft_strcmp(command->program, "export"))
		handle_export_command(command, ctx);
	if (command->redirections)
		restore_fds(saved_stdin, saved_stdout);
	return (1);
}

