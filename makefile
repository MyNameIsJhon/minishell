CC =gcc
CFLAGS =-I/usr/include -g 
LDFLAGS = 
EXEC =/usr/bin/minishell

INCLUDES = -I ./Libft/Libft -I ./Libft/List -I ./Libft -I ./get_shell  -I ./exec_shell -I ./exec_shell/path_finder -I ./errnoft

SRC = ./Libft/Libft/libft.c \
		./Libft/Libft/ft_strsjoin.c \
		./Libft/List/list.c \
		./Libft/ft_printf.c \
		./get_shell/g_shell.c \
		./exec_shell/path_finder/p_finder.c \
		./exec_shell/exec_shell.c \
		./errnoft/ft_errno.c \
		./Libft/get_next_line.c \
		./minishell.c

HEADS = ./Libft/Libft/libft.h \
		./Libft/List/list.h \
		./exec_shell/path_finder/p_finder.h \
		./exec_shell/exec_shell.h \
		./errnoft/ft_errno.h \
		./get_shell/g_shell.h
		
OBJ = $(SRC:.c=.o)

all : $(EXEC)

$(EXEC) : $(OBJ) 
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXEC) 

$(OBJ) : $(HEADS)

%.o :%.c  $(HEADS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<
	

.PHONY: all clean mrproper builtin_echo 

clean : 
	rm -rf $(OBJ)
	$(MAKE) clean -C builtins/src/echo
	$(MAKE) clean -C builtins/src/cd
	$(MAKE) clean -C builtins/src/env
	$(MAKE) clean -C builtins/src/setenv

mrproper : clean
	rm -rf $(EXEC)
	sudo rm -rf /usr/share/minishell
	sudo rm -rf /opt/minishell
	$(MAKE) mrproper -C builtins/src/echo
	$(MAKE) mrproper -C builtins/src/cd
	$(MAKE) mrproper -C builtins/src/env
	$(MAKE) mrproper -C builtins/src/setenv

builtins: all
	sudo cp -r ./var /usr/share/minishell
	sudo mkdir /opt/minishell/
	sudo chmod -R a+rwX /usr/share/minishell
	$(MAKE) -C builtins/src/echo
	$(MAKE) -C builtins/src/cd
	$(MAKE) -C builtins/src/env
	$(MAKE) -C builtins/src/setenv
	sudo cp -r ./builtins/execs /opt/minishell
	sudo chmod -R a+rwX /opt/minishell/


	




