/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:56:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:55:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Extracts and processes the content inside quotes.
**
** Steps:
** 1. If the current index points to the end of the string,
**    return NULL (no content to process).
** 2. Store the quote type (`'` or `"`) from the current
**    character.
** 3. Extract the content between the matching quotes using
**    `extract_quoted_content`, updating the parsing index.
**    - If extraction fails, return NULL.
** 4. If the quote type is a double quote (`"`), perform
**    variable expansion:
**    - Call `expand_variables` on the extracted string.
**    - Free the original unexpanded string.
**    - If expansion fails, return NULL.
**    - Replace `quoted` with the expanded result.
** 5. Return the processed quoted string.
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
** Appends quoted text to the value of the last TK_WORD token if no whitespace
** was found before it.

** 1. If there was whitespace before, do nothing and return 0.
** 2. Get the last token from the list.
** 3. If the last token does not exist or is not TK_WORD, return 0.
** 4. Concatenate the last token's value with `quoted` using `ft_strjoin`.
** 5. Free the old value and the quoted string.
** 6. If concatenation fails, return -1.
** 7. Assign the new concatenated string to the token's value.
** 8. Return 1 to indicate success.
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
** Processes a token that begins with a quote and adds it
** to the token list.
**
** Steps:
** 1. Extract the quoted content from the input using
**    `process_quoted_content`, updating the parsing index.
**    - If extraction fails, return 0 to indicate error.
** 2. Try appending the quoted content to the last word token
**    using `append_quoted_to_last_word_token`:
**    - If it returns 1, the append was successful; return 1.
**    - If it returns -1, an error occurred; return 0.
** 3. If not appended, create a new TK_WORD token with the
**    quoted content and add it to the token list.
** 4. Free the temporary `quoted` string.
** 5. Return 1 to indicate successful processing.
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
