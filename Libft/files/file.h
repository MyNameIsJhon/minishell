#ifndef FILES_INT
#define FILES_INT

#define SEEK_BEGIN 1
#define SEEK_ACTUAL 2
#define SEEK_ND 3

typedef struct FT_FILE{

    int fd;
    int pos;
    int flags;
    char *path;

} FT_FILE;

int ft_get_next_line(int fd, char **line);
FT_FILE *ft_fopen(const char *path, int right);
void ft_fclose(FT_FILE *file);
int ft_fseek(FT_FILE *file, unsigned int seek_loc, long nb_c);

void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(char const *s, int fd);
void ft_putnbr_fd(int n, int fd);

#endif