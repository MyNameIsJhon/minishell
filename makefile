CC =gcc
CFLAGS =-I/usr/include -g 
LDFLAGS = 
EXEC =minishell

INCLUDES = -I ./Libft/Libft -I ./Libft/List -I ./Libft -I ./get_shell  -I ./exec_shell -I ./exec_shell/path_finder -I ./errnoft -I ./builtins/ -I ./builtins/cd -I ./builtins/echo -I ./builtins/env -I ./builtins/setenv 

SRC = ./Libft/Libft/libft.c \
		./Libft/Libft/ft_strsjoin.c \
		./Libft/List/list.c \
		./Libft/ft_printf.c \
		./get_shell/g_shell.c \
		./exec_shell/path_finder/p_finder.c \
		./exec_shell/exec_shell.c \
		./errnoft/ft_errno.c \
		./Libft/get_next_line.c \
		./builtins/cd/cd.c \
		./builtins/echo/echo.c \
		./builtins/env/env.c \
		./builtins/setenv/setenv.c \
		./minishell.c

HEADS = ./Libft/Libft/libft.h \
		./Libft/List/list.h \
		./exec_shell/path_finder/p_finder.h \
		./exec_shell/exec_shell.h \
		./errnoft/ft_errno.h \
		./builtins/shell_builtins.h \
		./get_shell/g_shell.h
		
OBJ = $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : $(OBJ) 
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXEC) 

$(OBJ) : $(HEADS)

%.o :%.c  $(HEADS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	

.PHONY: all clean mrproper builtins

clean : 
	rm -rf $(OBJ)

mrproper : clean
	rm -rf $(EXEC)
	sudo rm -rf /usr/share/minishell

builtins: all
	sudo mkdir /usr/share/minishell/
	sudo cp ./var/env  /usr/share/minishell/
	sudo chmod -R a+rwX /usr/share/minishell
	


	




