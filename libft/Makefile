# === CONFIG ===

NAME        := libft.a
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g #-pthread #-fsanitize=undefined
AR          := ar rcs
RM          := rm -f
MKDIR_P     := mkdir -p
INCLUDES    := -Iincludes

# === PATHS ===

LIB_DIR     := libft
PRINTF_DIR  := ft_printf
ARENA_DIR	:= arena_allocator
FILE_DIR	:= fileft
OBJ_DIR     := obj
VEC_DIR		:= vector

SRC         := $(wildcard $(LIB_DIR)/*.c) $(wildcard $(PRINTF_DIR)/*.c) $(wildcard $(ARENA_DIR)/*.c) $(wildcard $(FILE_DIR)/*.c) $(wildcard $(VEC_DIR)/*.c)

OBJ         := $(SRC:%.c=$(OBJ_DIR)/%.o)

# === BUILD RULES ===

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Archiving into $(NAME)..."
	@$(AR) $@ $^
	@echo "Build complete."

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR_P) $(dir $@)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === CLEANUP ===

clean:
	@echo "Removing object files..."
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "Removing binary: $(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
