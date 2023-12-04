#include "libft.h"
#include <fcntl.h>
#include <stdlib.h> 
#include "shell_builtins.h"
#include "file.h"


int shell_env()
{
    extern char **environ;
    size_t i = 0;

    while(environ[i])
    {
        ft_putstr(environ[i]);
        ft_putchar('\n');
        i++;
    }

    return 0;
}