/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:17:16 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 22:25:02 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

/* =============================== */
/*       PARSING FUNCTIONS         */
/* =============================== */
int			is_separator(char c);
t_token		*create_token(char *value, int type);
void		add_token_to_list(t_token **head, t_token *new_token);
char		*extract_quoted_content(const char *str, int *index,
				char quote_char);
void		handle_redirection_token(const char *input, int *i,
				t_token **tokens);
int			handle_quoted_token(t_token_context *context);
void		handle_word_token(t_token_context *context);
t_token		*parse_line_to_tokens(const char *input, t_shell *shell);
t_token		*get_last_token(t_token *head);
void		init_token_context(t_token_context *context, t_init_params *params);
int			skip_whitespace_and_check(const char *str,
				int *i, int *had_whitespace);

#endif
