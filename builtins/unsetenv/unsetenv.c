#include "shell_builtins.h"
#include "libft.h"
#include "list.h"
#include <stdlib.h> 
#include <fcntl.h>
#include "file.h"

int shell_unsetenv(int argc, char **args)
{
    FT_FILE *file = NULL;
    t_list **alst;
    t_list *lst = NULL;

    if(!(*args) || !(args[1]))
    {
        ft_putstr("désoler mais vous devez rentrer une valeur\n");
        return 0;
    }
    if(!(file_2_lst(&lst, MEM_PATH)))
        return 0;
    alst = &lst;
    if(!(del_file(MEM_PATH)))
        return 0;
    if(!(new_file(MEM_PATH)))
        return 0;


    if(!(file = ft_fopen(MEM_PATH, O_RDWR)))
        return 0;

    while(lst != NULL)
    {
        if(ft_strncmp((const char*) lst->content, args[1], ft_chrlen(args[1], '=')) != 0)
        {
            ft_putstr_fd(lst->content, file->fd);
            ft_putchar_fd('\n', file->fd);
        }
        lst = lst->next;
    }

    ft_fclose(file);
    ft_lstclearall(alst, &free);

    return 1;    
}

