/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:17:16 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 15:30:21 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

/* =================== 1) PARSER ENTRY POINTS =============================== */
t_cmd		*convert_tokens_to_cmd_list(t_token *token_list, t_shell *shell);

/* =================== 2) VARIABLE & ENVIRONMENT EXPANSION ================== */
char		*expand_variables(char *input, t_shell *shell);
char		*expand_program_name(char *input, int pos, t_shell *shell);
char		*expand_exit_status(char *str, int start, t_shell *shell);
char		*expand_environment_variable(char *str, int start, int end,
				t_shell *shell);
char		*get_variable_value(char *str, int start, int end, t_shell *shell);
char		*create_expanded_string(char *before, char *value, char *after);
int			find_variable_end(char *str, int start);

/* ========================= 3) ARGUMENT PROCESSING ========================= */
int			populate_command_args(t_cmd *command, t_token *token_start);
char		**create_args_without_redirection(t_token *tokens);
char		**copy_args_to_array(t_token *tokens, char **args, int word_count);
int			count_valid_args(t_token *tokens);

/* ========================= 4) TOKEN PROCESSING =========================== */
int			handle_quoted_token(t_token_context *context);
void		handle_word_token(t_token_context *context);
char		*extract_and_expand_word(const char *input, int *i,
				t_shell *shell);

/* ======================= 5) REDIRECTION VALIDATION ======================== */
int			validate_input_redirections(t_token *tokens);
int			validate_in_redirections(t_token *tokens);
int			validate_heredoc_redirections(t_token *tokens);
int			validate_redirect_syntax(t_token *curr);
int			is_input_redir_target(t_token *tokens, t_token *curr);
int			is_redirection_file(t_token *tokens, t_token *curr);

/* ======================== 6) TOKEN LIST UTILITIES ========================= */
void		add_token_to_list(t_token **head, t_token *new_token);
t_token		*get_last_token(t_token *head);
t_token		*create_token_sublist(t_token *start, t_token *end);
char		*extract_raw_word(const char *input, int *i);
char		*unescape_unquoted(const char *s);

#endif
