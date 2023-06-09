#include "libft.h"
#include <fcntl.h>
#include <stdlib.h> 
#include "shell_builtins.h"
#include "file.h"

int shell_env()
{
    int fd = 0;
    char *line;
    int i = 0;


    if ((fd = open(MEM_PATH, O_RDONLY)) == -1)
    {
        ft_putstr("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    
    int ret;
    while ((ret = ft_get_next_line(fd, &line))  > 0)
    {
        ft_putstr(line);
        ft_putchar('\n');
        free(line);
    }
    
    if (ret == -1)
    {
        ft_putstr("Erreur lors de la lecture du fichier.\n");
        close(fd);
        return 1;
    }
    
    close(fd);
    
    return 0;
}