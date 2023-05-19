#include <unistd.h>
#include "libft.h"
#include "list.h"
#include "g_shell.h"
#include "ft_errno.h"

int program_finder(char *path, int flag)
{
    if(access(path, flag) == 0)
        return 1;
}

char *finder_to_path(char *prog_name)
{
    char *PATH = getenv("PATH");
    char **astr = NULL;

    char *r_path = NULL;

    int i = 0;

    astr = ft_strsplit(PATH, ':');
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