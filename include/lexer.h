/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:17:16 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 14:47:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structures.h"
# include "parser.h"

/* ===================== 1) TOKENIZATION ENTRY POINTS ====================== */
t_token		*parse_line_to_tokens(const char *str, t_shell *shell);
void		handle_word_token(t_token_context *context);
int			handle_quoted_token(t_token_context *context);
/* =================== 2) WHITESPACE & SEPARATORS ========================== */
int			skip_whitespace_and_check(const char *str, int *i,
				int *had_whitespace);
int			is_separator(char c);
int			only_spaces(const char *str);
/* ============ 3) WORD AND QUOTED STRING EXTRACTION ======================== */
char		*extract_and_expand_word(const char *input, int *i,
				t_shell *shell);
char		*extract_quoted_content(const char *str, int *index,
				char quote_char);
/* ======================= 4) REDIRECTION PARSING =========================== */
int			get_redir_type_and_length(char first, char second, int *length);
void		get_redir(const char *input, int *curr_pos, int *type,
				char **token_str);
void		handle_redirection_token(const char *input, int *curr_pos,
				t_token **tokens);
/* ===================== 5) TOKEN LIST MANAGEMENT =========================== */
void		add_token_to_list(t_token **head, t_token *new_token);
t_token		*get_last_token(t_token *head);
t_token		*create_token_sublist(t_token *start, t_token *end);
t_token		*create_token(char *value, int type);

#endif
