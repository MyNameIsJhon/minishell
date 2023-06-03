#ifndef SHELL_BUILTINS
#define SHELL_BUILTINS

#define  MEM_PATH "/usr/share/minishell/env"

int shell_env();
int shell_cd(int argc, char **argv);
int shell_echo(int argc, char **argv);
int shell_setenv(int argc, char **argv);
int shell_unsetenv(int argc, char **args);


#endif