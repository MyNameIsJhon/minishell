/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 22:03:32 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 22:23:56 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*mini_prompt(char *pwd, t_context *ctx)
{
	char	*prompt;
	char	*line;
	size_t	tot;

	tot = ft_strlen(ctx->user) + ft_strlen(ctx->hostname) + ft_strlen(pwd) + 10;
	prompt = arena_alloc(ctx->line_memory, tot + 1, 1);
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strlcat(prompt, ctx->user, tot + 1);
	ft_strlcat(prompt, "㉿", tot + 1);
	ft_strlcat(prompt, ctx->hostname, tot + 1);
	ft_strlcat(prompt, ":[", tot + 1);
	ft_strlcat(prompt, pwd, tot + 1);
	ft_strlcat(prompt, "] $ ", tot + 1);
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

/* t_context *init_minishell() */
/* { */
/* 	t_context *context; */
/**/
/* 	content = malloc(sizeof(t_context)); */
/* 		*/
/* } */

char	*get_user_input(t_context *ctx)
{
	char	*path;
	char	*input;

	path = arena_alloc(ctx->line_memory, 1024, 1);
	if (!path || !getcwd(path, 1024))
	{
		clear_history();
		context_free(&ctx);
		exit(1);
	}
	input = mini_prompt(path, ctx);
	if (!input)
	{
		clear_history();
		ft_putstr("exit\n");
		context_free(&ctx);
		exit(0);
	}
	return (input);
}

int	is_cmd_builtin(t_command *command)
{
	if (!ft_strcmp(command->com_splited[0], "cd")
		|| !ft_strcmp(command->com_splited[0], "exit")
		|| !ft_strcmp(command->com_splited[0], "env")
		|| !ft_strcmp(command->com_splited[0], "unset")
		|| !ft_strcmp(command->com_splited[0], "export")
		|| !ft_strcmp(command->com_splited[0], "echo")
		|| !ft_strcmp(command->com_splited[0], "pwd"))
		return (true);
	return (false);
}

char	execute_user_command(t_command *command, t_context *ctx)
{
	char		**env;
	t_command	*current;

	current = command;
	env = convert_env(ctx->env, ctx->line_memory);
	if (current->next && is_cmd_builtin(command) == true)
		return (run_cmd(command, env, ctx));
	if (is_cmd_builtin(command) == true)
		return (execute_builtin(command, ctx));
	while (current)
	{
		if (!find_prog(current, ctx))
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(command->com_splited[0], 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
		current = current->next;
	}
	return (run_cmd(command, env, ctx));
}
