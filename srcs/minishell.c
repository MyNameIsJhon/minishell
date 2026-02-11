/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:45 by jriga             #+#    #+#             */
/*   Updated: 2026/02/09 00:12:51 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*mini_prompt(char *pwd, t_context *ctx)
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

static char	*get_user_input(t_context *ctx)
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

static void	print_cmd_not_found(t_command *command)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(command->com_splited[0], 2);
	ft_putstr_fd("\n", 2);
}

static char	execute_user_command(t_command *command, char **envp,
		t_context *ctx)
{
	char	**env;

	(void)envp;
	if (!ft_strcmp(command->com_splited[0], "cd")
		|| !ft_strcmp(command->com_splited[0], "exit")
		|| !ft_strcmp(command->com_splited[0], "env")
		|| !ft_strcmp(command->com_splited[0], "unset")
		|| !ft_strcmp(command->com_splited[0], "export")
		|| !ft_strcmp(command->com_splited[0], "echo")
		|| !ft_strcmp(command->com_splited[0], "pwd"))
		return (execute_builtin(command, ctx));
	else if (!find_prog(command, ctx))
	{
		print_cmd_not_found(command);
		return (127);
	}
	env = convert_env(ctx->env, ctx->line_memory);
	return (run_cmd(command, env));
}

void	print_cmds(t_command *command)
{
	t_redir	*redir;
	int		i;

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
		command = command->next;
	}
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
		printf("return value: %d\n",execute_user_command(command, envp, ctx));
		/* print_cmds(command); */
	}
	context_free(&ctx);
	return (0);
}
