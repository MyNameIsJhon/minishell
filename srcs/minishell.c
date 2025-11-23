/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:45 by jriga             #+#    #+#             */
/*   Updated: 2025/11/23 03:02:46 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"
#include "fileft.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

/* char	*mini_prompt(void) */
/* { */
/* 		*/
/* } */

char	*mini_prompt(char *pwd, t_context *ctx)
{
	char	*prompt;
	char	*line;
	size_t	tot;

	tot = LEN_PROMPT + ft_strlen(pwd) + ft_strlen(ctx->user)
		+ ft_strlen(ctx->domain);
	prompt = arena_alloc(ctx->line_memory, tot + 1, 1);
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strlcat(prompt, "┌──(", tot + 1);
	ft_strlcat(prompt, ctx->user, tot + 1);
	ft_strlcat(prompt, "㉿", tot + 1);
	ft_strlcat(prompt, ctx->domain, tot + 1);
	ft_strlcat(prompt, ")-[", tot + 1);
	ft_strlcat(prompt, pwd, tot + 1);
	ft_strlcat(prompt, "]\n└─$ ", tot + 1);
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

static char	*get_user_input(t_context *ctx)
{
	char	*path;
	char	*input;

	path = arena_alloc(ctx->line_memory, 1024, 1);
	if (!path || !getcwd(path, 1024))
	{
		clear_history();
		exit(1);
	}
	input = mini_prompt(path, ctx);
	if (!input)
	{
		clear_history();
		exit(0);
	}
	return (input);
}

static void	print_cmd_not_found(t_command *command)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(command->program, 2);
	ft_putstr_fd("\n", 2);
}

static int	execute_user_command(t_command *command, char **envp,
		t_context *ctx)
{
	char	**env;

	(void)envp;
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
	else if (!find_prog(command, ctx))
	{
		print_cmd_not_found(command);
		return (0);
	}
	else
	{
		env = convert_env(ctx->env, ctx->line_memory);
		run_cmd(command, env);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*hello;
	t_command	*command;
	t_context	*ctx;

	(void)ac;
	(void)av;
	ctx = context_init();
	ctx->env = env_init(envp, ctx->global_memory);
	if (!ctx)
		return (1);
	while (1)
	{
		context_reset_line(ctx);
		hello = get_user_input(ctx);
		command = mini_parser(hello, ctx);
		free(hello);
		if (!command || !command->program)
			continue ;
		execute_user_command(command, envp, ctx);
	}
	context_free(&ctx);
	return (0);
}
