#include "shell_builtins.h"
#include "libft.h"
#include "list.h"
#include <stdlib.h> 
#include <fcntl.h>
#include "file.h"

size_t ft_strclen(char *str, char c)
{
    size_t i = 0;

    while (str[i] != c && str[i])
        i++;
    return i;
}

t_list **reload_env(int fd, char **env)
{
    t_list **alst = NULL;
    t_list *lst = NULL;

    char *line = NULL;

    int i = 0;
    int verif = 0;

    if (!(*env))
        return NULL;
    while (ft_get_next_line(fd, &line))
    {
        while (env[i] && verif == 0)
        {
            if (ft_strncmp(line, env[i], ft_strclen(line, '=')) == 0)
                verif = 1;
            i++;
        }
        if (verif == 0)
        {
            if (!lst)
            {
                lst = ft_lstnew((char*) ft_strdup(line));
                alst = &lst;
            }
            else
                ft_lstadd_back(alst, ft_lstnew((char*) ft_strdup(line)));
        }
        free(line);
    }
    close(fd);
    return alst;
}

int update_env(t_list **alst, int fd)
{
    t_list *lst = *alst;

    while (lst != NULL)
    {
        ft_putstr_fd((const char*) lst->content, fd);
        lst = lst->next;
    }

    close(fd);
    return 1;
}

int shell_unsetenv(int argc, char **args)
{
    int fd = 0;
    t_list **alst = NULL;

    if (argc <= 1)
        return 0;
    if ((fd = open(MEM_PATH, O_RDWR)) == -1)
        return 0;
    if ((alst = reload_env(fd, args)) == NULL)
    {
        close(fd);
        return 0;
    }
    if ((fd = open(MEM_PATH, O_WRONLY)) == -1)
        return 0;
    if (!(update_env(alst, fd)))
    {
        ft_lstclearall(alst, &free);
        close(fd);
        return 0;
    }

    ft_lstclearall(alst, &free);
    return 1;
}
