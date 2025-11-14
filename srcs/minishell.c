/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:03:45 by jriga             #+#    #+#             */
/*   Updated: 2025/11/12 11:55:56 by jriga            ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char		*hello;
	t_command	*command;
	/* t_context	*context; */
	char		*path;
	/* char		*result; */

	(void)ac;
	(void)av;
	while (1)
	{
		path = getcwd(NULL, 0);
		hello = mini_prompt(path, "mynameisjhon", "minishell");
		free(path);
		if (!hello)
			exit(0);
		command = mini_parser(hello);
		free(hello);
		if (!command || !command->program)
		{
			command_free(&command);
			continue ;
		}
		if (!ft_strcmp(command->program, "exit"))
		{
			command_free(&command);
			exit(0);
		}
		if (!find_prog(command))
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(command->program, 2);
			ft_putstr_fd("\n", 2);
			command_free(&command);
			continue ;
		}
		/* printf("path: %s\n", result); */
		/* command_print(command); */
		run_cmd(command, envp);
		command_free(&command);
	}
}
