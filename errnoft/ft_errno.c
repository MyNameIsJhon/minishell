#include <unistd.h>
#include "libft.h"
#include "ft_errno.h"

int INFINITE_STOP = 1;
int FILE_NOT_FOUND = 0;
int PROG_NOT_WORK = 0;

void ft_errno(char *str)
{
    if(FILE_NOT_FOUND == 1)
    {
        ft_putstr("Ce programme est introuvable : ");
        ft_putstr(str);
        ft_putstr(" !");
        ft_putstr("\n\n");
        INFINITE_STOP = 0;
    }
    if(PROG_NOT_WORK == 1)
    {
        ft_putstr(str);
        ft_putstr(" is not working, you can try other flags");
        ft_putstr(" !");
        ft_putstr("\n\n");
        INFINITE_STOP = 0;
    }
}