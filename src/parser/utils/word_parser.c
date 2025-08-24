/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:55:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:17:06 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** extract_and_expand_word
**
** This function extracts a raw word from the input and applies
** transformations (unescaping and variable expansion).
** - Call extract_raw_word() to read the word starting at *i.
** - If no word is found, return NULL.
** - If the word contains '*' not escaped with '\', treat it as
**   a literal "\*" (escape it) and set exit_status to 0.
** - Otherwise, call unescape_unquoted() to remove escape chars
**   outside of quotes.
** - Free the old word and keep the unescaped one.
** - Expand variables in the word using expand_variables().
** - Free the unescaped version and return the expanded word.
*/
char	*extract_and_expand_word(const char *input, int *i, t_shell *shell)
{
	char	*word;
	char	*unescaped;
	char	*expanded;

	word = extract_raw_word(input, i);
	if (!word)
		return (NULL);
	if (ft_strchr(word, '*') && !ft_strstr(word, "\\*"))
	{
		free(word);
		shell->exit_status = 0;
		return (ft_strdup("\\*"));
	}
	unescaped = unescape_unquoted(word);
	free(word);
	if (!unescaped)
		return (NULL);
	expanded = expand_variables(unescaped, shell);
	return (free(unescaped), expanded);
}

/*
** append_to_previous_word_token
**
** This function appends expanded text to the last TK_WORD token
** if no whitespace was encountered before it.
** - If context->had_whitespace is set, return 0 because the
**   expanded word must be treated as a new token.
** - Retrieve the last token from the list.
** - If no token exists or the last token is not TK_WORD, return 0.
** - Concatenate last_token->value with the expanded string.
**   * If concatenation fails, free expanded and return 1.
** - Replace the old token value with the new concatenated one.
** - Free the temporary expanded string.
** - Return 1 to indicate the string was appended successfully.
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
		return (free(expanded), 1);
	free(last_token->value);
	last_token->value = new_value;
	return (free(expanded), 1);
}

/*
** handle_word_token
**
** This function processes a word token from the input.
** - Calls extract_and_expand_word() to read the word and expand
**   any variables if present.
** - If extraction fails, return immediately.
** - If the word can be appended to the previous word token,
**   append it and return.
** - Otherwise, create a new TK_WORD token with the expanded word
**   and add it to the token list.
** - Free the temporary expanded string after adding the token.
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
