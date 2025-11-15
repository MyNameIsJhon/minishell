/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:45 by jriga             #+#    #+#             */
/*   Updated: 2025/11/15 01:37:47 by jriga            ###   ########.fr       */
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

char	*mini_prompt(char *pwd, char *user, char *dom)
{
	char	*prompt;
	char	*line;
	size_t	tot;

	tot = LEN_PROMPT + ft_strlen(pwd) + ft_strlen(user) + ft_strlen(dom);
	prompt = malloc(tot + 1);
	if (!prompt)
		return (NULL);
	prompt[0] = '\0';
	ft_strlcat(prompt, "┌──(", tot + 1);
	ft_strlcat(prompt, user, tot + 1);
	ft_strlcat(prompt, "㉿", tot + 1);
	ft_strlcat(prompt, dom, tot + 1);
	ft_strlcat(prompt, ")-[", tot + 1);
	ft_strlcat(prompt, pwd, tot + 1);
	ft_strlcat(prompt, "]\n└─$ ", tot + 1);
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	free(prompt);
	return (line);
}

/* t_context *init_minishell() */
/* { */
/* 	t_context *context; */
/**/
/* 	content = malloc(sizeof(t_context)); */
/* 	 */
/* } */

static char	*get_user_input(void)
{
	char	*path;
	char	*input;

	path = getcwd(NULL, 0);
	input = mini_prompt(path, "mynameisjhon", "minishell");
	free(path);
	if (!input)
	{
		clear_history();
		exit(0);
	}
	return (input);
}

static int	handle_exit_command(t_command *command)
{
	if (!ft_strcmp(command->program, "exit"))
	{
		command_free(&command);
		clear_history();
		exit(0);
	}
	return (0);
}

static int	handle_cd_command(t_command *command)
{
	if (!ft_strcmp(command->program, "cd"))
	{
		chdir(command->args[0]);
	}
	return (0);
}

static void	print_cmd_not_found(t_command *command)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(command->program, 2);
	ft_putstr_fd("\n", 2);
}

static int	execute_user_command(t_command *command, char **envp)
{
	if (!find_prog(command))
	{
		print_cmd_not_found(command);
		return (0);
	}
	run_cmd(command, envp);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char		*hello;
	t_command	*command;

	(void)ac;
	(void)av;
	while (1)
	{
		hello = get_user_input();
		command = mini_parser(hello);
		free(hello);
		if (!command || !command->program)
		{
			command_free(&command);
			continue ;
		}
		handle_cd_command(command);
		handle_exit_command(command);
		execute_user_command(command, envp);
		command_free(&command);
	}
}
