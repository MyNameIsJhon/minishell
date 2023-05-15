#include <unistd.h>
#include "libft.h"
#include "list.h"
#include "g_shell.h"
#include "stdio.h"

int FILE_NOT_FOUND = 0;

void ft_errno(char *str)
{
    if(FILE_NOT_FOUND == 1)
        printf("    No program of this name found : %s !", str);
    
}

void lst_printall(t_list **alst)
{
    t_list *lst = *alst;

    int i = 0;

    while(lst != NULL)
    {
        ft_printf("%s \n", (char*) lst->content);
        lst = lst->next;
    }
}

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

int main()
{
    char *shell = NULL;
    t_list *lst = NULL;

    char *prog_path = NULL;
    
    shell = get_shell();

    lst = shell_sep(shell);

    prog_path = finder_to_path((char*) lst->content);

    if(prog_path != NULL)
        ft_printf("%s \n", prog_path);

    ft_errno((char*) lst->content);

    ft_lstclearall(&lst, &free);
    free(shell);

    return 0;
}