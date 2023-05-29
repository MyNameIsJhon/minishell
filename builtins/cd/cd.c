#include <unistd.h>
#include "libft.h"
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>

void cd_error(char *path)
{
    ft_printf("%s: Le chemin est incorrect ou inaccessible\n", path);
}

int ft_is_dir(const char *path)
{
    struct stat file_stat;

    if (stat(path, &file_stat) != 0)
    {
        perror("Erreur lors de la récupération des informations sur le fichier");
        return 0;
    }

    if (S_ISDIR(file_stat.st_mode))
    {
        if (access(path, R_OK | X_OK) == 0)
            return 1;
    }

    return 0;
}

int shell_cd(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Veuillez fournir un chemin pour changer de répertoire\n");
        return 1;
    }

    if (!ft_is_dir(argv[1]))
    {
        cd_error(argv[1]);
        return 1;
    }

    ft_putnbr(1);

    if (chdir(argv[1]) != 0)
    {
        perror("Erreur lors du changement de répertoire");
        return 1;
    }
    else
    {
        ft_putnbr(2);
    }

    return 0;
}




