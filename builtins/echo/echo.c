#include <fcntl.h>
#include "libft.h"
#include "file.h"
#include "shell_builtins.h"

char *env_get(char *value)
{
    FT_FILE *file = NULL;
    char *line = NULL;
    int cont = 1;
    char **astr;

    if(!value)
        return NULL;
    if(!(file = ft_fopen(MEM_PATH, O_RDONLY)))
        return NULL;
    while(ft_fget_next_line(file, &line) && cont == 1)
    {
        if(ft_strncmp(value, line, ft_strlen(line)))
        {
            astr = ft_strsplit(line, '=');
            cont = 0;
        }

        free(line);
    }
    if(cont == 0)
    {
        line = ft_strdup(astr[1]);
        ft_free_strsplit(astr);
    }

    return line;
}

void echo_display(char *str)
{
    size_t i = 0;
    size_t y = 0;
    size_t var_len = 0;
    
    char *var_name = NULL;

    char *var_result = NULL;

    while(str[i])
    {
        if(str[i] == '$')
        {
            var_len = ft_strlen(str) - i;

            if(!(var_name = (char*) malloc(sizeof(char) * var_len + 1)))
                return;
            while(str[i])
            {
                var_name[y] = str[i];
                y++;
                i++;
            }
            var_name[y] = '\0';
            var_result = env_get(var_name);
            ft_printf("%s \n", var_result);

            free(var_name);
            free(var_result);
        }
        else
            ft_putchar(str[i]);

        i++;
    }
    
}

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
            echo_display(argv[i]);
        i++;

        ft_putchar(' ');
    }
}