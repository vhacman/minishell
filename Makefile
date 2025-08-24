# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 13:56:52 by vhacman           #+#    #+#              #
#    Updated: 2025/08/24 12:20:20 by vhacman          ###   ########.fr        #
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
# === SRC FILES =========
# =======================

SRC 		= \
			  clean_and_error/error.c \
			  clean_and_error/clean_utils.c \
			  clean_and_error/clean_token.c \
			  clean_and_error/clean_env.c \
			  clean_and_error/clean_shell.c \
			  clean_and_error/clean_cmd.c \
			  lexer/escape.c \
			  lexer/tokenizer_main.c \
			  lexer/token_lexer_utils.c \
			  lexer/tokenizer_utils.c \
			  lexer/token_redirection.c \
			  executor/prepare/exec_prepare.c \
			  executor/prepare/pipe_enviroment.c \
			  executor/prepare/args_convert.c \
			  executor/redirection/heredoc.c \
			  executor/redirection/redirect_output.c \
			  executor/redirection/file_operations.c \
			  executor/redirection/redirect_input.c \
			  executor/redirection/redirect_utils.c \
			  executor/redirection/redirect_handler.c \
			  executor/redirection/redir_in_setup.c \
			  executor/builtin/builtin_echo.c \
			  executor/builtin/builtin_pwd.c \
			  executor/builtin/built_in_exit/handle_exit.c \
			  executor/builtin/built_in_exit/exit_string_validation.c \
			  executor/builtin/built_in_cd/builtin_cd.c \
			  executor/builtin/built_in_cd/builtin_cd_actions.c \
			  executor/builtin/builtin_unset.c \
			  executor/builtin/handle_built_in.c \
			  executor/builtin/built_in_env/builtin_env.c \
			  executor/builtin/built_in_env/env_management/env_setters.c \
			  executor/builtin/built_in_env/env_management/env_set_utils.c \
			  executor/builtin/built_in_env/env_management/env_list_init.c \
			  executor/builtin/built_in_export/builtin_export.c \
			  executor/builtin/built_in_export/export_print.c \
			  executor/builtin/built_in_export/export_sort.c \
			  executor/builtin/built_in_export/export_parse.c \
			  executor/command_path/path_split_utils.c \
			  executor/command_path/env_path_split.c \
			  executor/command_path/path_search.c \
			  executor/pipeline/pipe_handler.c \
			  executor/pipeline/pipe_child_setup.c \
			  executor/pipeline/pipe_execution.c \
			  executor/pipeline/pipe_child_IO.c \
			  executor/pipeline/pipe_setup.c \
			  executor/pipeline/pipe_utils.c \
			  executor/signal/signal_utils.c \
			  executor/signal/signals.c \
			  executor/signal/signal_setup.c \
			  executor/process/exec_dispatch.c \
			  executor/process/fork_children.c \
			  executor/process/exec_builtins.c \
			  executor/process/process_handler.c \
			  core/main.c \
			  core/input/prompt_color.c \
			  core/input/input_handler.c \
			  core/input/prompt_helper.c \
			  parser/utils/token_list.c \
			  parser/utils/parser_utils.c \
			  parser/utils/token_parser.c \
			  parser/utils/word_parser.c \
			  parser/redirection/redirect_validation.c \
			  parser/redirection/args_filtering.c \
			  parser/pipe/pipe_command_builder.c \
			  parser/pipe/pipe_token_parser.c \
			  parser/expansion/variable_expander.c \
			  parser/expansion/env_expansion.c

# =======================
# === OBJ COMPILED ======
# =======================

OBJ        = $(SRC:%.c=$(OBJ_DIR)/%.o)

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
	@echo "$(GREEN)minishell$(RESET)"


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
