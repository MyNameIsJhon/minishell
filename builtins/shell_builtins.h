#ifndef SHELL_BUILTINS
#define SHELL_BUILTINS

#define  MEM_PATH "/usr/share/minishell/env"

extern char **env_minishell;

int shell_env();
int shell_cd(int argc, char **argv);
int shell_echo(int argc, char **argv);
int shell_setenv(int argc, char **argv);
int shell_unsetenv(int argc, char **args);
char *ft_getenv(char *s);
char *ft_getenv_case(char *s);//retourne ligne case tableau env correspondant


#endif