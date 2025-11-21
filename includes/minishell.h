/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:07:59 by jriga             #+#    #+#             */
/*   Updated: 2025/11/21 04:09:51 by jriga            ###   ########.fr       */
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

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_command
{
	char			*program;
	char			**args;
	char			**com_splited;
	t_token			*tokens;
	char			**paths;
	int				exec_maxlen;
	char			*exec_path;
	t_arena			*memory;
	int				size;
}					t_command;

typedef struct s_context
{
	t_env			*env;
	t_arena			*global_memory;
	t_arena			*line_memory;
	char			*user;
	char			*domain;
	int				paths_maxlen;
}					t_context;

t_context			*context_init(void);
void				context_free(t_context **ctx);
void				context_reset_line(t_context *ctx);
t_command			*mini_parser(char *user_input, t_context *ctx);
void				command_print(t_command *command);
char				*find_prog(t_command *command);
int					run_cmd(t_command *command, char **envp);
char				**get_executable_paths(t_command *cmd);

t_token				*tokenize(char *input, t_arena *memory);
void				print_tokens(t_token *tokens);
int					is_separator(char c);
void				add_token(t_token **head, t_token **tail, t_token_type type,
						char *value, t_arena *memory);
int					extract_quoted(char *input, int i, t_token **head,
						t_token **tail, t_arena *memory);
int					extract_word(char *input, int i, t_token **head,
						t_token **tail, t_arena *memory);
int					handle_operator(char *input, int i, t_token **head,
						t_token **tail, t_arena *memory);
int					handle_exit_command(t_command *command, t_context *ctx);
t_env				*env_init(char **envp, t_arena *memory);
t_env				*new_env(char *name, char *value, t_arena *memory);
void				env_add_back(t_env *env, t_env **envs);
void				env_delete(char *name, t_env **envs);
t_env				*find_env(char *name, t_env *envs);
void				print_env(t_env *envs);
int					handle_unset_command(t_command *cmd, t_context *ctx);
int	handle_export_command(t_command *cmd, t_context *ctx);

#endif
