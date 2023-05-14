#include <unistd.h>
#include "libft.h"
#include "list.h"

#define BUFF_CARACTS 350


size_t char_len_shells(const char *str, size_t start)
{
    size_t i = start;
    int bo = (-1);

    if(!str)
        return 0;
    while(str[i] == ' ')
        i++;
    while(str[i] != '\0')
    {
        if(str[i] == '\"' || str[i] == '\'')
            bo *= (-1);
        else if(str[i] == ' ' && bo == -1)
            break;
        i++;
    }
    return i - start;
}


char get_char() {
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

void minishell_prompt()
{
    ft_putstr("minishell㉿kali$>");
}

char *get_shell()
{
    char *str = NULL;
    char *shell = NULL;
    char c = 'i';
    int i = 0;

    if(!(str = (char*) malloc(sizeof(char) * BUFF_CARACTS)))
        return NULL;

    minishell_prompt();
    
    while(c != '\n' && i < BUFF_CARACTS)
    {
        c = get_char();
        str[i] = c;
        i++;
    }
    
    str[i] = '\0';

    shell = ft_strdup(str);

    free(str);

    return shell;
}

t_list *shell_sep(char *shell)
{
    t_list *lst = NULL;
    int i = 0;
    int y = 0;
    int z = 0; // compteur pour LST
    size_t len_val = 0;
    char *str = NULL;
    char c;

    size_t start = 0;    

    if(!shell)
        return NULL;
    while(shell[start] != '\0')
    {
        len_val = char_len_shells(shell, start);

        if(!(str = (char*) malloc(sizeof(char) * (len_val + 1))))
        {
            if(lst != NULL)
                ft_lstclearall(&lst, &free);
            return NULL;
        }
        while(i < len_val)
        {
            str[i] = shell[start+i];
            i++;
        }
        str[i] = '\0';
        if(z == 0)
            lst = ft_lstnew((char*) ft_strdup(str));
        else
            ft_lstadd_back(&lst, ft_lstnew((char*) ft_strdup(str)));
        
        start += len_val;

        while(shell[start] == ' ' && shell[start] != '\0')
            start++;
        
        free(str);
        z++;
        i = 0;
    }

    return lst;
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

int main()
{
    char *shell = NULL;
    t_list *lst = NULL;

    shell = get_shell();

    lst = shell_sep(shell);

    lst_printall(&lst);

    ft_lstclearall(&lst, &free);
    free(shell);
    return 0;
}