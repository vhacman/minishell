/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_colors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:15:32 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 22:39:14 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_COLORS_H
# define MACRO_COLORS_H

/* =============================== */
/*          TOKEN TYPES            */
/* =============================== */
/*
** Token types used by the lexer/parser:
** TK_WORD: command names, arguments, filenames, etc.
** TK_PIPE: pipe symbol '|', separates commands in a pipeline
** TK_IN: input redirection '<'
** TK_OUT: output redirection '>'
** TK_APPEND: output append redirection '>>'
** TK_HEREDOC: here-document redirection '<<'
*/
# define TK_WORD        0
# define TK_PIPE        1
# define TK_IN          2
# define TK_OUT         3
# define TK_APPEND      4
# define TK_HEREDOC     5
/* =============================== */
/*         ANSI COLOR CODES        */
/* =============================== */
/* ANSI escape codes for terminal colors used in prompt */
# define RESET          "\033[0m"
# define GREEN          "\033[32m"
# define BLUE           "\033[34m"
# define RED            "\033[31m"

#endif
