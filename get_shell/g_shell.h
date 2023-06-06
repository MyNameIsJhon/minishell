#ifndef G_SHELL
#define G_SHELL

size_t char_len_shells(const char *str, size_t start);
void minishell_prompt();
char *get_shell(char *username);
t_list *shell_sep(char *shell);

#endif