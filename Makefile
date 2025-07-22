# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 13:56:52 by vhacman           #+#    #+#              #
#    Updated: 2025/05/29 16:18:26 by vhacman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =======================
# === COMPILING RULE=====
# =======================

CC          = cc
CFLAGS      = -Wall -Wextra -Werror \
			  -Iinclude -Ilibft/includes


# =======================
# === DIRECTORY =========
# =======================

SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = libft

# =======================
# === BONARY NAME  ======
# =======================

NAME 		= minishell

# =======================
# === FIND SOURCES ======
# =======================

SRC         := $(shell find $(SRC_DIR) -name "*.c")
OBJ 		:= $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC:.c=.o))

# # =======================
# # === SRC FILES =========
# # =======================

# SRC 		= \

# =======================
# === OBJ COMPILED ======
# =======================

# OBJ        = $(SRC:%.c=$(OBJ_DIR)/%.o)

# =======================
# === LIBRARIES==========
# =======================

LIBFT       = $(LIBFT_DIR)/libft.a

# =======================
# === COLOURS OUTPUT ====
# =======================

GREEN       = \033[0;32m
CYAN        = \033[0;36m
YELLOW      = \033[1;33m
RESET       = \033[0m


all: $(NAME)
	@echo "$(GREEN)compiling minishell$(RESET)"


# =======================
# === LINKING MANDATORY =
# =======================

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(YELLOW)🔧 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)


# =======================
# === COMPILING    ======
# =======================

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)🛠️  Compiling: %-45s$(RESET)\n" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

# =======================
# === BUILD LIBFT       =
# =======================

$(LIBFT):
	@echo "$(CYAN)📦 Building libft...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR)

# =======================
# === CLEANING ==========
# =======================

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean

fclean: clean
	@echo "$(YELLOW)🗑️  Removing executable...$(RESET)"
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

# =======================
# === TARGET FINTI ======
# =======================

.PHONY: all clean fclean re


# =======================
# === TEST ONLY LIBFT ===
# =======================

test_libft:
	@echo "$(CYAN)🔍 Testing libft build...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR)
