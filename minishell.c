#include <unistd.h>
#include "libft.h"
#include "list.h"
#include "g_shell.h"
#include "stdio.h"

int FILE_NOT_FOUND = 0;

void ft_errno(char *str)
{
    if(FILE_NOT_FOUND == 1)
    {
        ft_putstr("Ce programme est introuvable : ");
        ft_putstr(str);
        ft_putstr(" !");
        ft_putstr("\n\n");
    }
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

int main()
{
    char *shell = NULL;
    t_list *lst = NULL;

    int infinite_stop = 1;

    char *prog_path = NULL;

    char **args = NULL;


    while(infinite_stop == 1)
    {
        FILE_NOT_FOUND = 0;

        shell = get_shell();

        lst = shell_sep(shell);

        args = ft_lst_to_argv(&lst);
        
        if(lst != NULL)
            prog_path = finder_to_path((char*) lst->content);
        if(prog_path != NULL)
        {
            ft_printf("%s \n", prog_path);
            //execve(prog_path, args, NULL);
        }
        if(lst != NULL)
        {
            if(ft_strcmp((char*) lst->content, "exit") == 0)
                infinite_stop = 0;
            ft_errno((char*) lst->content);
            ft_lstclearall(&lst, &free);
        }
        if(shell != NULL)
            free(shell);
        if(args != NULL)
            ft_free_strsplit(args);
    }
    return 0;
}
