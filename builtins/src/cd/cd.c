#include <unistd.h>
#include "libft.h"
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>

void cd_error(char *path)
{
    ft_printf("%s: Le chemin est incorrect ou inaccessible\n", path);
}

int ft_is_dir(struct stat *file_stat, char *path)
{
    if (S_ISDIR(file_stat->st_mode))
    {
        if (access(path, R_OK | X_OK) == 0)
            return 1;
        else
            return 0;
    }
    return 0;
}

int main(int argc, char **argv)
{
    struct stat file_stat;

    if (argc < 2)
    {
        printf("Veuillez fournir un chemin pour changer de répertoire\n");
        return 1;
    }
    if (lstat(argv[1], &file_stat) != 0)
    {
        perror("Erreur lors de la récupération des informations sur le fichier");
        return 1;
    }
    if (!ft_is_dir(&file_stat, argv[1]))
    {
        cd_error(argv[1]);
        return 1;
    }

    if (chdir(argv[1]) != 0)
    {
        perror("Erreur lors du changement de répertoire");
        return 1;
    }

    return 0;
}



