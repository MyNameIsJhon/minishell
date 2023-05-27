#include <unistd.h>
#include "libft.h"
#include "list.h"
#include "g_shell.h"
#include "ft_errno.h"
#include "p_finder.h"

int program_finder(char *path, int flag)
{
    if(access(path, flag) == 0)
        return 1;
}

char *builtins_to_path(char *PATH, char *built_path)
{
    char *str = NULL;

    str = ft_strsjoin(3, built_path, ":", PATH);

    return str;
}

char *finder_to_path(char *prog_name)
{
    char *PATH = getenv("PATH");
    char **astr = NULL;

    char *r_path = NULL;

    char *PATHS = NULL;

    int i = 0;

    PATHS = builtins_to_path(PATH, BUILTINS);

    astr = ft_strsplit(PATHS, ':');
    if(prog_name == NULL)
        return NULL;
    if(ft_strcmp(prog_name, "exit") == 0)
        return NULL;
    while(astr[i] != NULL)
    {
        r_path = ft_strsjoin(3, astr[i], "/", prog_name);

        if(access(r_path, X_OK) == 0)
        {
            ft_free_strsplit(astr);
            return r_path;
        }
        i++;
        free(r_path);
    }
    FILE_NOT_FOUND = 1;
    ft_free_strsplit(astr);
    return NULL;
}
