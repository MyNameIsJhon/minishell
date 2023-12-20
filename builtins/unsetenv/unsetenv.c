#include "shell_builtins.h"
#include "libft.h"
#include "list.h"
#include <stdlib.h> 
#include <fcntl.h>
#include "file.h"

size_t env_len(const char **tab)// besoin de configurer nouveau env propre à mon programme
{
    size_t i = 0;

    while(tab[i] != NULL)
        i++;
    return i;
}

char **env_order(char *caser)
{
    size_t i = 0;
    size_t y = 0;
    extern char **environ;
    char **tab = NULL;

    if(!caser || !environ)
        return environ;
    else
        tab = malloc(sizeof(char*) * env_len(environ));
    while(environ[i+y])
    {
        if(ft_strcmp(caser, environ[i]) == 0)
           y++;
        tab[i] = environ[i+y];
        i++;
    }
    tab[i] = NULL;

    return tab;
}

int shell_unsetenv(int argc, char **args)
{
    char *caser = NULL;
    extern char **environ;

    if(!(*args) || !(args[1]) || !environ)
    {
        ft_putstr("désoler mais vous devez rentrer une valeur\n");
        return 0;
    }

    caser = ft_getenv_case(args[1]);

    free(caser);
        
    env_order(caser);
    
}

