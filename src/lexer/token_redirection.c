/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:56:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:35:26 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** get_redir_type_and_length
**
** This function determines the type of a redirection operator and
** its length in characters.
** - If the operator is "<<", set length to 2 and return TK_HEREDOC.
** - If the operator is ">>", set length to 2 and return TK_APPEND.
** - If the operator is ">", set length to 1 and return TK_OUT.
** - Otherwise (only "<"), set length to 1 and return TK_IN.
*/
int	get_redir_type_and_length(char first, char second, int *length)
{
	if (first == '<' && second == '<')
		return (*length = 2, TK_HEREDOC);
	else if (first == '>' && second == '>')
		return (*length = 2, TK_APPEND);
	else if (first == '>')
		return (*length = 1, TK_OUT);
	else
		return (*length = 1, TK_IN);
}

/*
** get_redir
**
** This function identifies a redirection operator in the input.
** - Reads the current and next character from input.
** - Calls get_redir_type_and_length() to determine the token type
**   (>, >>, <, <<) and how many characters to consume.
** - Advances curr_pos by the length of the operator.
** - Based on the type, duplicates the correct string ("<", ">",
**   "<<", ">>") and stores it in *token_str.
*/
void	get_redir(const char *input, int *curr_pos, int *type,
					char **token_str)
{
	char	first;
	char	second;
	int		length;

	first = input[*curr_pos];
	second = input[*curr_pos + 1];
	*type = get_redir_type_and_length(first, second, &length);
	*curr_pos += length;
	if (*type == TK_HEREDOC)
		*token_str = ft_strdup("<<");
	else if (*type == TK_APPEND)
		*token_str = ft_strdup(">>");
	else if (*type == TK_OUT)
		*token_str = ft_strdup(">");
	else
		*token_str = ft_strdup("<");
}

/*
** handle_redirection_token
**
** This function processes a redirection operator in the input.
** - Calls get_redir() to identify the redirection type (>, >>,
**   <, <<) and extract the corresponding string.
** - Creates a new token with the redirection type and value.
** - Adds the new token to the token list.
** - Frees the temporary string used for the token value.
*/
void	handle_redirection_token(const char *input, int *curr_pos,
								t_token **tokens)
{
	int			type;
	char		*token_str;
	t_token		*new_tok;

	get_redir(input, curr_pos, &type, &token_str);
	new_tok = create_token(token_str, type);
	add_token_to_list(tokens, new_tok);
	free(token_str);
}
