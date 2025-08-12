/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:56:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 16:22:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
