#include <unistd.h>
#include "libft.h"
#include "list.h"
#include "g_shell.h"
#include "ft_errno.h"
#include "p_finder.h"
#include "exec_shell.h"
#include <stdio.h>
#include <fcntl.h>
#include "shell_builtins.h"


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


int main()
{ 
    char *shell = NULL;
    t_list *lst = NULL;

    char *prog_path = NULL;

    char **args = NULL;

    char *username = NULL;


    username = get_username();

    while(INFINITE_STOP == 1)
    {

        shell = get_shell(username);

        lst = shell_sep(shell);

        args = ft_lst_to_argv(&lst);
        
        if(lst != NULL)
            prog_path = finder_to_path((char*) lst->content);
        if(prog_path != NULL)
        {
            shell_exec(prog_path, args);
        }
        if(lst != NULL)
        {
            if(ft_strcmp((char*) lst->content, "exit") == 0)
                INFINITE_STOP = 0;
            ft_errno((char*) lst->content);
            ft_lstclearall(&lst, &free);
        }
        if(shell != NULL)
            free(shell);
        if(args != NULL)
            ft_free_strsplit(args);
    }

    free(username);
    return 0;
}