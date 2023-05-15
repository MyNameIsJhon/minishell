CC =gcc
CFLAGS =-I/usr/include -g 
LDFLAGS = 
EXEC =minishell

INCLUDES = -I ./Libft/Libft -I ./Libft/List -I ./Libft -I ./get_shell -I ./file_access

SRC = ./Libft/Libft/libft.c \
		./Libft/Libft/ft_strsjoin.c \
		./Libft/List/list.c \
		./Libft/ft_printf.c \
		./get_shell/g_shell.c \
		./file_access/f_access.c \
		./minishell.c

HEADS = ./Libft/Libft/libft.h \
		./Libft/List/list.h \
		./file_access/f_access.h \
		./get_shell/g_shell.h
		
OBJ = $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : $(OBJ) 
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXEC) 

$(OBJ) : $(HEADS)

%.o :%.c  $(HEADS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	

.PHONY : clean mrproper

clean : 
	rm -rf $(OBJ)

mrproper : clean
	rm -rf $(EXEC)

