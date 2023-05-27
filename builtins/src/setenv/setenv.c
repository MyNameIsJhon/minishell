#include "libft.h"
#include <fcntl.h>
#include <stdlib.h> 

#define  MEM_PATH "/usr/share/minishell/env"

int main(int argc, char **argv) // problème lorsque le programme est utilisé en dehors du repertoire minishell
{
    int fd = 0;
    char *line;
    int i = 1;
    

    if((fd = open(MEM_PATH, O_RDWR)) == -1)
    {
        ft_printf("%s : Erreur lors de l'ouverture du fichier.\n", argv[0]);
        return 1;
    }
    if(!argv[1] || !argv[2])
    {
        ft_printf("%s : Désoler mais vous avez introduis trop peux de valeurs\n", argv[0]);
        close(fd);
        return 1;
    }
    ft_putstr_fd(argv[1], fd);
    ft_putchar_fd('=', fd);
    ft_putstr_fd(argv[2], fd);
    ft_putchar_fd('\n', fd);
    
    close(fd);

    return 0;
}