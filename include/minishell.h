/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begiovan <begiovan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:00:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/06 15:47:48 by begiovan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* =============================== */
/*          SYSTEM INCLUDES        */
/* =============================== */
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <limits.h>

/* =============================== */
/*         PROJECT INCLUDES        */
/* =============================== */
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "structures.h"
# include "macro_colors.h"
# include "builtins.h"
# include "clean.h"
# include "signals.h"
# include "parser.h"


/* =============================== */
/*            CONSTANTS            */
/* =============================== */
# define PATH_MAX 4096

/* =============================== */
/*         GLOBAL VARIABLES        */
/* =============================== */
/*
** Global variable holding the last received signal number.
** Used to safely communicate signal events between handlers
** and the main shell loop.
*/
extern volatile sig_atomic_t	g_signal;

/* =============================== */
/*          CORE FUNCTIONS         */
/* =============================== */
void		init_shell(t_shell *shell);
int			start_colored_prompt(t_shell *shell);
void		handle_input(char *input, t_shell *shell);
char		*get_current_directory(void);
int			only_spaces(const char *str);
char		*expand_program_name(char *input, int pos, t_shell *shell);

/* =============================== */
/*      EXECUTION FUNCTIONS        */
/* =============================== */
int			execute_command(t_token *tokens, t_shell *shell);
int			execute_command_type(char **args, t_shell *shell);
char		*find_command_path(char *command);
int			execute_external_command(char *cmd_path, char **args,
				t_shell *shell);
char		**convert_tokens_to_args(t_token *tokens);


/* =============================== */
/*      EXPANSION FUNCTIONS        */
/* =============================== */
char		*expand_variables(char *input, t_shell *shell);
char		*get_variable_value(char *str, int start, int end, t_shell *shell);
char		*expand_exit_status(char *str, int start, t_shell *shell);
char		*expand_environment_variable(char *str, int start, int end,
				t_shell *shell);
int			find_variable_end(char *str, int start);
char		*create_expanded_string(char *before, char *value, char *after);

/* =============================== */
/*       ERROR FUNCTIONS           */
/* =============================== */
void		exit_with_error(char *msg, void *context, int flag, int use_errno);
int			print_error(char *msg);
int			print_pipe_error(void);

/* =============================== */
/*     REDIRECTIONS FUNCTIONS      */
/* =============================== */
int			handle_pipe(t_cmd *cmd1, t_cmd *cmd2, t_shell *shell);
int			execute_pipeline(t_cmd *cmds, t_shell *shell);
int			check_for_pipes(t_token *tokens);
t_cmd		*create_new_cmd(void);
t_token		*create_token_sublist(t_token *start, t_token *end);
t_cmd		*convert_tokens_to_cmd_list(t_token *tokens, t_shell *shell);
int			check_syntax_pipes(t_token *tokens);
int			execute_cmd_in_pipe(t_cmd *cmd, t_shell *shell);
int			setup_command_execution(t_cmd *curr, int prev_fd, int *pipe_fd, pid_t *pid);
// int			handle_child_process(t_cmd *curr, int prev_fd, int *pipe_fd, t_shell *shell);
int			execute_single_command(t_cmd *curr, int prev_fd, int *pipe_fd, t_shell *shell);
int			fork_second_child(t_cmd *cmd2, t_shell *shell, int pipe_fd[2], pid_t pid1);
int			fork_first_child(t_cmd *cmd1, t_shell *shell, int pipe_fd[2]);
int			setup_child_pipe(int pipe_fd[2], int is_left);
int			create_pipe_and_setup(int pipe_fd[2]);
int			handle_special_cases(char *input, t_shell *shell);


void		execute_child_process(t_cmd *curr, int prev_fd, int *pipe_fd, t_shell *shell);



// redirect 
void 		restore_redirection(t_shell *shell);
int 		handle_redirection_with_tokens(t_token *tokens, t_shell *shell);
char 		**create_args_without_redirection(t_token *tokens);
int 		open_file_with_type(char *filename, int redirect_type);
char 		*get_filename_from_next_token(t_token *redirect_token);
t_token 	*find_redirection_token(t_token *tokens, int *redirect_type);

#endif
