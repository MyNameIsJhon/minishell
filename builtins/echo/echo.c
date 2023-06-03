#include "libft.h"
#include "file.h"

void print_out_char(char *str, char c)
{
    int i = 0;

    while(str[i])
    {
        if(str[i] == c)
            continue;
        ft_putchar(str[i]);
        i++;
    }
}

int shell_echo(int argc, char **argv)
{
    int i = 1;
    int y = 1;

    while(argv[i] != NULL)
    {
        if(argv[i][0] == '\'' && argv[i][ft_strlen(argv[i])] == '\'')
            print_out_char(argv[i], '\'');
        else if(argv[i][0] == '"' && argv[i][ft_strlen(argv[i])] == '"')
            print_out_char(argv[i], '"');
        else
            ft_putstr(argv[i]);
        i++;

        ft_putchar(' ');
    }
}