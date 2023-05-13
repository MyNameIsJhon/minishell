#include <unistd.h>
#include "libft.h"
#include "list.h"

#define BUFF_CARACTS 350

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


int main()
{
    char *shell = NULL;

    shell = get_shell();


    free(shell);
    return 0;
}