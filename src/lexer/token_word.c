/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:55:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:12:59 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Extracts a non-quoted, non-space word from the input and expands variables.
**
** - i: Pointer to current parsing index, updated as characters are read.
** Process:
** 1. Store the starting position of the word.
** 2. Increment index while:
**    - Not a space.
**    - Not a command separator (|, <, >, etc.).
**    - Not a quote character.
** 3. Calculate extracted length. If length ≤ 0, return NULL.
** 4. Copy the substring from `start` to current index.
** 5. Expand any variables in the word using `expand_variables`.
** 6. Free the original word and return the expanded string.
**
*/
char	*extract_and_expand_word(const char *input, int *i, t_shell *shell)
{
	int		start;
	char	*word;
	char	*expanded;
	int		len;

	start = *i;
	while (input[*i] && input[*i] != ' '
		&& !is_separator(input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	len = *i - start;
	if (len <= 0)
		return (NULL);
	word = ft_substr(input, start, *i - start);
	if (!word)
		return (NULL);
	expanded = expand_variables(word, shell);
	return (free(word), expanded);
}

/*
** Appends expanded text to the value of the last TK_WORD token if possible.
** 1. If whitespace was encountered before, do not append and return 0.
** 2. Get the last token from the list.
** 3. If no token exists or last token is not TK_WORD, return 0.
** 4. Join the last token's value with `expanded` using `ft_strjoin`.
** 5. If joining fails, free `expanded` and return 1 (error).
** 6. Replace the old token value with the new concatenated string.
** 7. Free `expanded` and return 1 (success).
*/
static int	append_to_previous_word_token(t_token_context *context,
						char *expanded)
{
	t_token	*last_token;
	char	*new_value;

	if (context->had_whitespace)
		return (0);
	last_token = get_last_token(*(context->tokens));
	if (!last_token || last_token->type != TK_WORD)
		return (0);
	new_value = ft_strjoin(last_token->value, expanded);
	if (!new_value)
		return  (free(expanded), 1);
	free(last_token->value);
	last_token->value = new_value;
	return (free(expanded), 1);
}

/*
** Handles the creation or appending of a TK_WORD token during parsing.
**
** 1. Extract and expand the next word from the input using
**    `extract_and_expand_word`.
** 2. If no word is found or allocation fails, exit the function.
** 3. Attempt to append the expanded word to the last TK_WORD token
**    via `append_to_previous_word_token`.
**    - If appended, return immediately.
** 4. If not appended, create a new TK_WORD token and add it to the list.
** 5. Free the `expanded` string after token creation.
*/
void	handle_word_token(t_token_context *context)
{
	char	*expanded;

	expanded = extract_and_expand_word(context->input, context->i,
			context->shell);
	if (!expanded)
		return ;
	if (append_to_previous_word_token(context, expanded))
		return ;
	add_token_to_list(context->tokens, create_token(expanded, TK_WORD));
	free(expanded);
}
