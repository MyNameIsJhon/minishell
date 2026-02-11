/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:45 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 22:10:11 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmds(t_command *command)
{
	t_redir	*redir;
	int		i;

	printf("\n---Printing prog---\n\n");
	while (command)
	{
		redir = command->redirections;
		printf("prog name: %s\n", command->com_splited[0]);
		i = 0;
		while (command->com_splited[i])
		{
			printf("  arg[%d]: %s\n", i, command->com_splited[i]);
			i++;
		}
		while (redir)
		{
			printf("  redir type: %d\n", redir->type);
			redir = redir->next;
		}
		if (command->exec_path)
			printf("  exec_path: %s\n", command->exec_path);
		else
			printf("exec_path: (null)");
		command = command->next;
	}
	printf("\n");
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_command	*command;
	t_context	*ctx;

	(void)ac;
	(void)av;
	init_signals();
	ctx = context_init();
	ctx->env = env_init(envp, ctx->global_memory);
	if (!ctx)
		return (1);
	while (1)
	{
		context_reset_line(ctx);
		line = get_user_input(ctx);
		command = mini_parser(line, ctx);
		free(line);
		if (!command || !command->com_splited[0])
			continue ;
		printf("return value: %d\n", execute_user_command(command, ctx));
		print_cmds(command);
	}
	context_free(&ctx);
	return (0);
}
