CC =gcc
CFLAGS =-I/usr/include -g 
LDFLAGS = 
EXEC =../../execs/echo

INCLUDES = -I ../../../Libft/Libft -I ../../../Libft/List -I ../../../Libft 

SRC = ../../../Libft/Libft/libft.c \
		../../../Libft/Libft/ft_strsjoin.c \
		../../../Libft/List/list.c \
		../../../Libft/ft_printf.c \
		./echo.c

HEADS = ../../../Libft/Libft/libft.h \
		../../../Libft/List/list.h 
		
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