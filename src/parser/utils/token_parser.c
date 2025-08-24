/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:56:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:33:55 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** process_quoted_content
**
** This helper function extracts and processes the content inside
** quotes from the input string.
** - If the current character is the quote, store its type
**   (single or double).
** - Call extract_quoted_content() to get the text between the
**   opening and closing quotes.
** - If no content is found, return NULL.
** - If the quote type is double ("), expand variables inside the
**   quoted string using expand_variables().
** - The old quoted string is freed, and the expanded version is
**   used instead.
** - Return the final quoted string (allocated), or NULL on error.
*/
static char	*process_quoted_content(const char *input, int *i, t_shell *shell)
{
	char	*quoted;
	char	*expanded;
	char	quote_type;

	if (!input[*i])
		return (NULL);
	quote_type = input[*i];
	quoted = extract_quoted_content(input, i, quote_type);
	if (!quoted)
		return (NULL);
	if (quote_type == '"')
	{
		expanded = expand_variables(quoted, shell);
		free(quoted);
		if (!expanded)
			return (NULL);
		quoted = expanded;
	}
	return (quoted);
}

/*
** append_quoted_to_last_word_token
**
** This helper function tries to append a quoted string to the
** last word token, if possible.
** - If there was whitespace before the quoted string, return 0,
**   because it should not be merged with the previous token.
** - Get the last token from the token list.
** - If no token exists, or it is not a TK_WORD, return 0.
** - Otherwise, join the last token's value with the quoted text.
** - Free the old strings after joining.
** - If allocation fails, return -1 to signal an error.
** - If successful, update the last token's value and return 1.
*/
static int	append_quoted_to_last_word_token(t_token_context *context,
				char *quoted)
{
	t_token	*last_token;
	char	*new_value;

	if (context->had_whitespace)
		return (0);
	last_token = get_last_token(*(context->tokens));
	if (!last_token || last_token->type != TK_WORD)
		return (0);
	new_value = ft_strjoin(last_token->value, quoted);
	free_parts(last_token->value, quoted, NULL);
	if (!new_value)
		return (-1);
	last_token->value = new_value;
	return (1);
}

/*
** handle_quoted_token
**
** This function handles a token that starts with quotes.
** - Calls process_quoted_content() to extract the quoted text
**   and handle escapes if needed.
** - If extraction fails, return 0 (error).
** - The quoted string may be appended to the last word token:
**     * If result is 1, it was successfully appended → return 1.
**     * If result is -1, an error occurred → return 0.
** - Otherwise, create a new TK_WORD token with the quoted string
**   and add it to the token list.
** - The quoted string is then freed, and the function returns 1.
*/
int	handle_quoted_token(t_token_context *context)
{
	char	*quoted;
	int		result;

	quoted = process_quoted_content(context->input, context->i, context->shell);
	if (!quoted)
		return (0);
	result = append_quoted_to_last_word_token(context, quoted);
	if (result == 1)
		return (1);
	if (result == -1)
		return (0);
	add_token_to_list(context->tokens, create_token(quoted, TK_WORD));
	free_parts(quoted, NULL, NULL);
	return (1);
}
