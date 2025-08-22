/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:17:16 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 14:13:48 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structures.h"
# include "parser.h"

/* ===================== 1) TOKENIZATION ENTRY POINTS ====================== */
t_token		*parse_line_to_tokens(const char *str, t_shell *shell);

/* ======================== 2) INPUT VALIDATION ============================= */
int			has_unclosed_quotes(const char *str);
int			only_spaces(const char *str);
char		*get_complete_input(char *initial_input);

/* ====================== 3) STRING UTILITIES =============================== */
char		*ft_trim_spaces(const char *str);

/* =================== 4) WHITESPACE & SEPARATORS =========================== */
int			skip_whitespace_and_check(const char *str, int *i,
				int *had_whitespace);
int			is_separator(char c);

/* ============ 5) WORD AND QUOTED STRING EXTRACTION ======================== */
char		*extract_quoted_content(const char *str, int *index,
				char quote_char);

/* ======================= 6) REDIRECTION PARSING =========================== */
int			get_redir_type_and_length(char first, char second, int *length);
void		get_redir(const char *input, int *curr_pos, int *type,
				char **token_str);
void		handle_redirection_token(const char *input, int *curr_pos,
				t_token **tokens);

/* ===================== 7) TOKEN MANAGEMENT =============================== */
t_token		*create_token(char *value, int type);

#endif
