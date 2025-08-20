/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:17:16 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 18:00:51 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structures.h"

/* =================== 1) TOKEN → COMMAND LIST CONVERSION =================== */
t_cmd		*convert_tokens_to_cmd_list(t_token *token_list, t_shell *shell);
/* ========================= 2) ARGUMENT POPULATION ========================= */
int			populate_command_args(t_cmd *command, t_token *token_start);
/* ================= 3) VARIABLE & ENVIRONMENT EXPANSION ==================== */
char		*expand_program_name(char *input, int pos, t_shell *shell);
char		*create_expanded_string(char *before, char *value, char *after);
char		*expand_exit_status(char *str, int start, t_shell *shell);
int			find_variable_end(char *str, int start);
char		*get_variable_value(char *str, int start, int end, t_shell *shell);
char		*expand_variables(char *input, t_shell *shell);
char		*expand_environment_variable(char *str, int start, int end,
				t_shell *shell);
int is_redirection_file(t_token *tokens, t_token *curr);
char **copy_args_to_array(t_token *tokens, char **args, int word_count);
int	validate_heredoc_redirections(t_token *tokens);

#endif
