#include "libft.h"
#include <fcntl.h>
#include <stdlib.h> 
#include "shell_builtins.h"
#include "file.h"

char *ft_getenv(char *s)//renvoie dire
{
    int i = 0;
    t_list *lst;
    size_t s_len = 0;

    s_len = ft_strlen(s);

    while(env_minishell[i] != NULL)
    {
        if(ft_strncmp(env_minishell[i], s, s_len) == 0)
            return ft_strsub(env_minishell[i], s_len + 1, ft_strlen(env_minishell[i]) - (s_len + 1));
        i++;
    }

    ft_putstr("Aucune valeur trouvé\n");


    return NULL;
}

char *ft_getenv_case(char *s)//retourne ligne case tableau env correspondant
{
    int i = 0;
    t_list *lst;
    size_t s_len = 0;

    s_len = ft_strlen(s);

    while(env_minishell[i] != NULL)
    {
        if(ft_strncmp(env_minishell[i], s, s_len) == 0)
            return env_minishell[i];
        i++;
    }

    
    ft_putstr("Aucune valeur trouvé\n");


    return NULL;
}



