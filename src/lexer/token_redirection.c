/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:56:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:57:23 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Determines the redirection token type and its length.
** Process:
** 1. Check if the operator is `<<` → set length to 2 and return TK_HEREDOC.
** 2. Check if the operator is `>>` → set length to 2 and return TK_APPEND.
** 3. If only `>` is found → set length to 1 and return TK_OUT.
** 4. Otherwise, default to `<` → set length to 1 and return TK_IN.
**
** Returns:
** - The corresponding token type for the redirection operator.
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
** Extracts a redirection operator from the input string.
**
** Process:
** 1. Read the current and next characters from `input`.
** 2. Determine the redirection type and its length using
**    `get_redir_type_and_length`.
** 3. Advance `curr_pos` by the detected operator length.
** 4. Allocate and store the correct redirection string
**    ("<<", ">>", ">", or "<") in `token_str`.
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
** Creates and appends a redirection token to the token list.
** Process:
** 1. Call `get_redir` to identify the redirection type and extract its string.
** 2. Create a new token with the extracted string and type.
** 3. Add the new token to the token list.
** 4. Free the temporary string used for the token.
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
