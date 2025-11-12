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

# === COLORS / ICONS ===

BOLD        := \033[1m
GREEN       := \033[0;32m
YELLOW      := \033[0;33m
CYAN        := \033[0;36m
RESET       := \033[0m

# === BUILD RULES ===

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(CYAN)[🔧] Archiving into $(NAME)...$(RESET)"
	@$(AR) $@ $^
	@echo "$(GREEN)[✅] Build complete.$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR_P) $(dir $@)
	@echo "$(YELLOW)[⚙️] Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === CLEANUP ===

clean:
	@echo "$(CYAN)[🧹] Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "$(CYAN)[💥] Removing binary: $(NAME)$(RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
