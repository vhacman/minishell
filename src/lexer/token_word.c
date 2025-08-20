/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:55:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 18:59:06 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
