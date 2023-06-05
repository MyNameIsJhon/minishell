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

    if(!(*args))
        return 0;
    if(!(file = ft_fopen(MEM_PATH, O_WRONLY)))
        return 0;
    if(!(file_2_lst(alst, MEM_PATH)))
        return 0;
    lst = *alst;

    while(lst != NULL)
    {
        if(ft_strncmp(lst->content, args[1], ft_strlen(args[1])) != 0)
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
