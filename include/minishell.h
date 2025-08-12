/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:00:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 14:56:33 by vhacman          ###   ########.fr       */
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
# include "clean.h"
# include "parser.h"
# include "lexer.h"
# include "executor.h"

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
int			handle_special_cases(char *input, t_shell *shell);

/* =============================== */
/*       ERROR FUNCTIONS           */
/* =============================== */
void		exit_with_error(char *msg, void *context, int flag, int use_errno);
int			print_error(char *msg);
int			print_pipe_error(void);

#endif
