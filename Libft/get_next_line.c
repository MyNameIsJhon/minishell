#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"
#include "list.h"

#define BUFF_SIZE 34 //nombre max de caractère lu

char *strdup_chr(const char *str, char c)
{
    int i = 0;

    char *sub;

    while(str[i] != '\n' && str[i] != EOF)
        i++;
    
    sub = ft_strsub(str, 0, i-1);

    return sub;
}

int ft_get_next_line(int fd, char **line)
{
    char *str = (char*) malloc(sizeof(char) * BUFF_SIZE + 1);
    char *str_cpy = (char*) malloc(sizeof(char) * BUFF_SIZE + 1);

    if (!str || !str_cpy)
        return -1;

    if (read(fd, str, BUFF_SIZE) <= 0) {
        free(str);
        return 0;
    }
    
    str[BUFF_SIZE] = '\0';
    
    str_cpy = strdup_chr(str, '\n');
    *line = str_cpy;

    free(str);

    return 1;
}
