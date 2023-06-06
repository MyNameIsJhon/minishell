#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "libft.h"
#include "list.h"
#include "g_shell.h"
#include "ft_errno.h"
#include "p_finder.h"
#include "file.h"

int program_finder(char *path, int flag)
{
    if(access(path, flag) == 0)
        return 1;
}
int if_builtin(char *path)
{
    if(ft_strcmp(path, "./builtins/env") == 0)
        return 1;

    else if(ft_strcmp(path, "./builtins/setenv") == 0)
        return 1;

    else if(ft_strcmp(path, "./builtins/cd") == 0)
        return 1;

    else if(ft_strcmp(path, "./builtins/echo") == 0)
        return 1;
        
    else if(ft_strcmp(path, "./builtins/unsetenv") == 0)
        return 1;
        
    else
        return 0;

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

    PATHS = builtins_to_path(PATH, BUILTINS); //pour le moment totalement inutile mais en attente amélioration pour des builts extérieur

    astr = ft_strsplit(PATHS, ':');
    if(prog_name == NULL)
        return NULL;
    if(ft_strcmp(prog_name, "exit") == 0)
        return NULL;
    while(astr[i] != NULL)
    {
        r_path = ft_strsjoin(3, astr[i], "/", prog_name);

        if(if_builtin(r_path))
        {
            ft_free_strsplit(astr);
            return r_path;
        }
        else if(access(r_path, X_OK) == 0 )
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

char *get_user_repertory() 
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    char *user_pwd = NULL;

    if(pw != NULL)
        user_pwd = ft_strdup(pw->pw_dir);

    return user_pwd;
}

char *get_username() 
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    char *username = NULL;

    if(pw != NULL) 
        username = ft_strdup(pw->pw_name);

    return username;
}
