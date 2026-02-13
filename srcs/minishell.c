/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:45 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 22:46:42 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	print_cmds(t_command *command) */
/* { */
/* 	t_redir	*redir; */
/* 	int		i; */
/**/
/* 	printf("\n---Printing prog---\n\n"); */
/* 	while (command) */
/* 	{ */
/* 		redir = command->redirections; */
/* 		printf("prog name: %s\n", command->com_splited[0]); */
/* 		i = 0; */
/* 		while (command->com_splited[i]) */
/* 		{ */
/* 			printf("  arg[%d]: %s\n", i, command->com_splited[i]); */
/* 			i++; */
/* 		} */
/* 		while (redir) */
/* 		{ */
/* 			printf("  redir type: %d\n", redir->type); */
/* 			redir = redir->next; */
/* 		} */
/* 		if (command->exec_path) */
/* 			printf("  exec_path: %s\n", command->exec_path); */
/* 		else */
/* 			printf("exec_path: (null)"); */
/* 		command = command->next; */
/* 	} */
/* 	printf("\n"); */
/* } */

void	restore_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin >= 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout >= 0)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

static void	handle_empty_cmd(t_command *command)
{
	int	saved_in;
	int	saved_out;

	if (!command->redirections)
		return ;
	if (apply_redirections_with_backup(command->redirections,
			&saved_in, &saved_out) >= 0)
		restore_fds(saved_in, saved_out);
}

static int loop_main(t_context *ctx)
{
	char		*line;
	t_command	*command;

	init_signals();
	rl_catch_signals = 0;
	context_reset_line(ctx);
	line = get_user_input(ctx);
	if (!line)
		return (1);
	command = mini_parser(line, ctx);
	free(line);
	if (!command)
		return (0);
	if (!command->com_splited[0])
	{
		handle_empty_cmd(command);
		return (0);
	}
	ctx->last_exit_status = execute_user_command(command, ctx);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_context	*ctx;

	(void)ac;
	(void)av;
	ctx = context_init();
	ctx->env = env_init(envp, ctx->global_memory);
	if (!ctx)
		return (1);
	while (1)
	{
		if (loop_main(ctx) == 1)
			return (1);
	}
	context_free(&ctx);
	return (0);
}
