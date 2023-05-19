#include <unistd.h>
#include "libft.h"
#include "list.h"
#include "g_shell.h"
#include "ft_errno.h"
#include "p_finder.h"
#include <stdio.h>


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
