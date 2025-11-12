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

#include "libft.h"
#include "minishell.h"
#include "fileft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "arena_allocator.h"
/* char	*mini_prompt() */
/* { */
/* 	 */
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
	free(prompt);
	return (line);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char *hello;
	t_command *command;
	char	*path;
	
	while (1)
	{
		path = getcwd(NULL, 0);
		hello = mini_prompt(path, "mynameisjhon", "minishell");
		command = mini_parser(hello);
		exec_prog(command);
		command_print(command);
		command_free(&command);
		free(hello);
	}
}
