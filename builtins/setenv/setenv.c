#include "libft.h"
#include <fcntl.h>
#include <stdlib.h> 
#include "shell_builtins.h"
#include "file.h"


int shell_setenv(int argc, char **argv) // problème lorsque le programme est utilisé en dehors du repertoire minishell
{
    FT_FILE *file = NULL;
    char *line;
    int i = 1;
    int d = 0;

    if(!(file = ft_fopen(MEM_PATH, O_RDWR)))
    {
        ft_printf("%s : Erreur lors de l'ouverture du fichier.\n", argv[0]);
        return 1;
    }
    if(!argv[1])
    {
        ft_printf("%s : Désoler mais vous devez introduire une valeur\n", argv[0]);
        ft_fclose(file);
        return 1;
    }
    
    shell_unsetenv(argc, argv);

    ft_fseek(file, SEEK_END, 0);

    ft_putstr_fd(argv[1], file->fd);
    ft_putchar_fd('=', file->fd);

    if(argv[2] != NULL)
        ft_putstr_fd(argv[2], file->fd);

    ft_putchar_fd('\n', file->fd);
    
    ft_fclose(file);

    return 0;
}