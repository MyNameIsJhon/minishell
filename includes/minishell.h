/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:07:59 by jriga             #+#    #+#             */
/*   Updated: 2026/02/11 22:20:34 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "arena_allocator.h"
# include "fileft.h"
# include "libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXEC_MAXLEN 256
# define LEN_PROMPT 30
# define USER_POS 5
# define DOM_POS 6
# define PWD_POS 9
# define SEPARATORS " \t|<>\"'"
# define OPERATORS "|<>"
# define QUOTES "\'\""

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	char				quote_type;
	struct s_token		*next;
}						t_token;

typedef struct s_tokenizer
{
	t_token				*head;
	t_token				*tail;
	t_arena				*memory;
}						t_tokenizer;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_redir
{
	t_token_type		type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**com_splited;
	t_redir				*redirections;
	char				**paths;
	int					exec_maxlen;
	char				*exec_path;
	t_arena				*memory;
	int					fd[2];
	struct s_command	*next;
}						t_command;

typedef struct s_context
{
	t_env				*env;
	t_arena				*global_memory;
	t_arena				*line_memory;
	char				*user;
	char				*hostname;
	int					paths_maxlen;
	int					last_exit_status;
}						t_context;

t_context				*context_init(void);
void					context_free(t_context **ctx);
void					context_reset_line(t_context *ctx);
t_command				*mini_parser(char *user_input, t_context *ctx);
void					command_print(t_command *command);
char					*find_prog(t_command *command, t_context *ctx);
char					run_cmd(t_command *command, char **envp);
char					**get_executable_paths(t_command *cmd, t_context *ctx);

t_token					*tokenize(char *input, t_arena *memory);
void					print_tokens(t_token *tokens);
int						is_separator(char c);
void					add_token(t_tokenizer *tok, t_token_type type,
							char *value);
int						extract_quoted(char *input, int i, t_tokenizer *tok);
int						extract_word(char *input, int i, t_tokenizer *tok);
int						handle_operator(char *input, int i, t_tokenizer *tok);
int						handle_exit_command(t_command *command, t_context *ctx);
t_env					*env_init(char **envp, t_arena *memory);
t_env					*new_env(char *name, char *value, t_arena *memory);
void					env_add_back(t_env *env, t_env **envs);
void					env_delete(char *name, t_env **envs);
t_env					*find_env(char *name, t_env *envs);
void					print_env(t_env *envs);
int						handle_unset_command(t_command *cmd, t_context *ctx);
int						handle_export_command(t_command *cmd, t_context *ctx);
char					**convert_env(t_env *env, t_arena *memory);
int						handle_cd_command(t_command *command, t_context *ctx);

void					expand_tokens(t_tokenizer *tokenizer, t_context *ctx);
char					*expand_variables(char *str, t_context *ctx);
void					init_signals(void);

t_redir					*new_redir(t_token_type type, char *file,
							t_arena *memory);
void					redir_add_back(t_redir **head, t_redir *new);
t_redir					*extract_redirections(t_token **tokens,
							t_arena *memory);
int						apply_redirections(t_redir *redirs);
int						apply_redirections_with_backup(t_redir *redirs,
							int *saved_stdin, int *saved_stdout);
void					restore_fds(int saved_stdin, int saved_stdout);
int						execute_builtin(t_command *command, t_context *ctx);
int						handle_echo_command(t_command *cmd);
int						handle_pwd_command(void);
char					**recup_vars_in_token(t_token *token, t_arena *memory);
int						count_len_expandeds(char **vars, t_context *ctx);
int						count_len_vars(char **vars);
char					*get_user_input(t_context *ctx);
char					execute_user_command(t_command *command,
							t_context *ctx);
int						count_tokens(t_token *tokens);
void					init_command_struct(t_command *cmd, char **split);
t_command				*build_command(t_token *tokens, t_arena *memory);
t_token					*split_at_pipe(t_token **segment);

#endif
