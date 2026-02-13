# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minishell <minishell@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/12 00:00:00 by minishell         #+#    #+#              #
#    Updated: 2025/11/18 00:23:36 by jriga            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                   CONFIG                                     #
# ============================================================================ #

NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
DFLAGS      := -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
LDLIBS      := -lreadline
RM          := rm -f
MKDIR_P     := mkdir -p

# ============================================================================ #
#                                   PATHS                                      #
# ============================================================================ #

SRC_DIR     := srcs
BUILTINS_DIR := builtins
OBJ_DIR     := obj
INC_DIR     := includes
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

# ============================================================================ #
#                                   SOURCES                                    #
# ============================================================================ #


SRCS := builtins.c  echo.c       executor.c  expander_utils.c  input.c      parser_utils.c  redirections_utils.c  tokenizer.c cd.c        env.c        exit.c      export.c          minishell.c  pwd.c           signals.c             tokenizer_utils.c context.c   env_utils.c  expander.c  finder.c          parser.c     redirections.c   unset.c
OBJS := $(SRCS:.c=.o)
SRCS := $(addprefix $(SRCDIR)/, $(SRCS))
OBJS := $(addprefix $(OBJ_DIR)/, $(OBJS))
BUILTINS    := $(wildcard $(BUILTINS_DIR)/*.c)
BUILTINS_OBJS := $(BUILTINS:$(BUILTINS_DIR)/%.c=$(OBJ_DIR)/builtins/%.o)
DEPS        := $(OBJS:.o=.d) $(BUILTINS_OBJS:.o=.d)
INCLUDES    := -I$(INC_DIR) -I$(LIBFT_DIR)/includes

# ============================================================================ #
#                                   RULES                                      #
# ============================================================================ #

.PHONY: all clean fclean re debug help

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(BUILTINS_OBJS)
	@echo "Linking executable $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(BUILTINS_OBJS) -L$(LIBFT_DIR) -lft $(LDLIBS) -o $@
	@echo "Build complete: $(NAME)"
	@echo ""

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "Libft ready."
	@echo ""

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR_P) $(dir $@)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(OBJ_DIR)/builtins/%.o: $(BUILTINS_DIR)/%.c
	@$(MKDIR_P) $(dir $@)
	@echo "Compiling builtin: $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# ============================================================================ #
#                                   DEBUG                                      #
# ============================================================================ #

debug: CFLAGS += $(DFLAGS)
debug: fclean $(NAME)
	@echo "Debug build ready with sanitizers"

# ============================================================================ #
#                                   CLEANUP                                    #
# ============================================================================ #

clean:
	@echo "Cleaning object files..."
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo " Clean complete."

fclean: clean
	@echo "Removing executable: $(NAME)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo " Full clean complete."

re: fclean all

# ============================================================================ #
#                                   HELP                                       #
# ============================================================================ #

help:
	@echo "Minishell Makefile Commands:"
	@echo ""
	@echo "  make or $(BOLD)make all    - Build the project"
	@echo "  make debug           - Build with sanitizers (address + undefined)"
	@echo "  make clean           - Remove object files"
	@echo "  make fclean          - Remove object files and executable"
	@echo "  make re              - Rebuild everything from scratch"
	@echo "  make help            - Show this help message"
	@echo ""

# ============================================================================ #
#                                DEPENDENCIES                                  #
# ============================================================================ #

-include $(DEPS)
