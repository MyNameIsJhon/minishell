#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"
#include "list.h"
#include "ft_errno.h"
#include "exec_shell.h"
#include "shell_builtins.h"
#include "file.h"

size_t multitab_len(char **args)
{
    size_t i = 0;

    while(args[i] != NULL)
        i++;
    return i;
}


int exec_builtin(char **args)
{
    if(ft_strcmp(args[0], "env") == 0)
        shell_env();

    else if(ft_strcmp(args[0], "setenv") == 0)
        shell_setenv(multitab_len(args), args);

    else if(ft_strcmp(args[0], "cd") == 0)
        shell_cd(multitab_len(args), args);

    else if(ft_strcmp(args[0], "echo") == 0)
        shell_echo(multitab_len(args), args);

    else if(ft_strcmp(args[0], "unsetenv") == 0)
        shell_unsetenv(multitab_len(args), args);

    else
        return 0;

    return 1;
}

int exec_prog(char *path, char **args) 
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) 
    {
        perror("fork");
        return 0;
    } 
    else if (pid == 0) 
    {
        execve(path, args, NULL);
        _exit(1); 
    } 
    else 
    {
        if(waitpid(pid, &status, 0) == -1) 
            return 0;
    }
    return 1;
}

int shell_exec(char *path, char **args)
{
    if(exec_builtin(args) == 0)
    {
        if(exec_prog(path, args) == 1)
            return 1;
    }
    else
        return 1;

    return 0;
}







