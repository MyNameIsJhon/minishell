/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:07:59 by jriga             #+#    #+#             */
/*   Updated: 2025/11/12 15:34:10 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "arena_allocator.h"
# include "libft.h"
# define EXEC_MAXLEN 256
# define LEN_PROMPT 30
# define USER_POS 5
# define DOM_POS 6
# define PWD_POS 9

typedef struct s_env
{
	char	*name;
	char	*value;
}			t_env;

typedef struct s_context
{
	t_env	**env;
	t_arena	*memory;
	t_arena	*line_memory;
	char	**paths;
	int		paths_maxlen;
}			t_context;

typedef struct s_command
{
	char	*program;
	char	**args;
	char	**com_splited;
	char	**paths;
	int		exec_maxlen;
	char	*exec_path;
}			t_command;

t_command	*mini_parser(char *user_input);
void		command_free(t_command **command);
void		command_print(t_command *command);
char		*find_prog(t_command *command);
int	run_cmd(t_command *command, char **envp);

#endif
