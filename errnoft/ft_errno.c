#include <unistd.h>
#include "libft.h"
#include "ft_errno.h"

void ft_errno(char *str)
{
    if(FILE_NOT_FOUND == 1)
    {
        ft_putstr("Ce programme est introuvable : ");
        ft_putstr(str);
        ft_putstr(" !");
        ft_putstr("\n\n");
    }
}