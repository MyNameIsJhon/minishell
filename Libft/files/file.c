#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "list.h"
#include "file.h"


FT_FILE *ft_fopen(const char *path, int right)
{
    FT_FILE *file;

    file = (FT_FILE*) malloc(sizeof(FT_FILE));
    if (file == NULL)
        return NULL;

    file->fd = open(path, right);
    if (file->fd == -1)
    {
        free(file);
        return NULL;
    }
    
    file->pos = 0;
    file->flags = right;
    file->path = ft_strdup(path);

    return file;
}

void ft_fclose(FT_FILE *file)
{
    if (file == NULL)
        return;

    close(file->fd);
    free(file->path);
    free(file);
}

void newbuff_fd()

size_t ft_fdlen(int fd)
{
    char c;
    size_t i = 0;

    if (fd == 0)
        return 0;

    while (read(fd, &c, 1))
        i++;
    
    return i;
}

int ft_fseek(FT_FILE *file, unsigned int seek_loc, long nb_c)
{
    long i = 0;
    char c;
    char *path;
    int right;

    if (file == NULL || seek_loc > 3 || access(file->path, R_OK))
        return 0;
    
    if (seek_loc == SEEK_BEGIN)
    {
        path = ft_strdup(file->path);
        right = file->flags;
        ft_fclose(file);
        file = ft_fopen(path, right);
        free(path);
    }
    else if (seek_loc == SEEK_END)
        nb_c = ft_fdlen(file->fd) - nb_c;

    while (i < nb_c && read(file->fd, &c, 1) > 0)
        i++;

    return 1;
}

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void ft_putstr_fd(char const *s, int fd)
{
    write(fd, s, ft_strlen(s));
}

void ft_putnbr_fd(int n, int fd)
{
    if (n < 0)
    {
        ft_putchar_fd('-', fd);
        n = -n;
    }
    if (n > 9)
        ft_putnbr_fd(n / 10, fd);
    ft_putchar_fd(n % 10 + '0', fd);
}

int main(void)
{
    FT_FILE *file;
    char *line;

    file = ft_fopen("./file.txt", O_RDWR);
    if (file == NULL)
    {
        ft_putstr("bug");
        return 1;
    }

    ft_fseek(file, SEEK_BEGIN, 0);

    ft_get_next_line(file->fd, &line);
    ft_putstr(line);

    ft_fclose(file);

    return 0;
}
