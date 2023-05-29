#ifndef EXEC_SHELL
#define EXEC_SHELL

int exec_builtin(char **args);
int exec_prog(char *path, char **args);
int shell_exec(char *path, char **args);

#endif 