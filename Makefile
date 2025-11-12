# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minishell <minishell@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/12 00:00:00 by minishell         #+#    #+#              #
#    Updated: 2025/01/12 00:00:00 by minishell        ###   ########.fr        #
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
OBJ_DIR     := obj
INC_DIR     := includes
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

# ============================================================================ #
#                                   SOURCES                                    #
# ============================================================================ #

SRCS        := $(wildcard $(SRC_DIR)/*.c)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

INCLUDES    := -I$(INC_DIR) -I$(LIBFT_DIR)/includes

# ============================================================================ #
#                                   COLORS                                     #
# ============================================================================ #

BOLD        := \033[1m
GREEN       := \033[0;32m
YELLOW      := \033[0;33m
CYAN        := \033[0;36m
RED         := \033[0;31m
RESET       := \033[0m

# ============================================================================ #
#                                   RULES                                      #
# ============================================================================ #

.PHONY: all clean fclean re debug help

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(CYAN)$(BOLD)[🔗] Linking executable $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LDLIBS) -o $@
	@echo "$(GREEN)$(BOLD)[✅] Build complete: $(NAME)$(RESET)"
	@echo ""

$(LIBFT):
	@echo "$(CYAN)$(BOLD)[📚] Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)$(BOLD)[✅] Libft ready.$(RESET)"
	@echo ""

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR_P) $(dir $@)
	@echo "$(YELLOW)[⚙️ ] Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# ============================================================================ #
#                                   DEBUG                                      #
# ============================================================================ #

debug: CFLAGS += $(DFLAGS)
debug: fclean $(NAME)
	@echo "$(BOLD)$(GREEN)[🐛] Debug build ready with sanitizers$(RESET)"

# ============================================================================ #
#                                   CLEANUP                                    #
# ============================================================================ #

clean:
	@echo "$(CYAN)[🧹] Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)[✅] Clean complete.$(RESET)"

fclean: clean
	@echo "$(CYAN)[💥] Removing executable: $(NAME)$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)[✅] Full clean complete.$(RESET)"

re: fclean all

# ============================================================================ #
#                                   HELP                                       #
# ============================================================================ #

help:
	@echo "$(BOLD)$(CYAN)Minishell Makefile Commands:$(RESET)"
	@echo ""
	@echo "  $(BOLD)make$(RESET) or $(BOLD)make all$(RESET)    - Build the project"
	@echo "  $(BOLD)make debug$(RESET)           - Build with sanitizers (address + undefined)"
	@echo "  $(BOLD)make clean$(RESET)           - Remove object files"
	@echo "  $(BOLD)make fclean$(RESET)          - Remove object files and executable"
	@echo "  $(BOLD)make re$(RESET)              - Rebuild everything from scratch"
	@echo "  $(BOLD)make help$(RESET)            - Show this help message"
	@echo ""

# ============================================================================ #
#                                DEPENDENCIES                                  #
# ============================================================================ #

-include $(DEPS)
