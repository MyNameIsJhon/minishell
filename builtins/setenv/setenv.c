#include "libft.h"
#include <fcntl.h>
#include <stdlib.h> 
#include "shell_builtins.h"
#include "file.h"


int shell_setenv(int argc, char **argv) // problème lorsque le programme est utilisé en dehors du repertoire minishell
{
    int fd = 0;
    char *line;
    int i = 1;
    int d = 0;

    if((fd = open(MEM_PATH, O_RDWR)) == -1)
    {
        ft_printf("%s : Erreur lors de l'ouverture du fichier.\n", argv[0]);
        return 1;
    }
    if(!argv[1])
    {
        ft_printf("%s : Désoler mais vous devez introduire une valeur\n", argv[0]);
        close(fd);
        return 1;
    }

    while(ft_get_next_line(fd, &line))

    ft_putstr_fd(argv[1], fd);
    ft_putchar_fd('=', fd);

    if(argv[2] != NULL)
        ft_putstr_fd(argv[2], fd);

    ft_putchar_fd('\n', fd);
    
    close(fd);

    return 0;
}