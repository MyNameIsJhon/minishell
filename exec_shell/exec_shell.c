#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"
#include "list.h"
#include "ft_errno.h"

int exec_prog(char *path, char **args, char *prog_name) 
{
    pid_t pid;
    int status;

    pid = fork();

    ft_printf("%s\n", path);

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







