/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:55:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/04 16:16:38 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_and_expand_word(const char *input, int *i, t_shell *shell)
{
	int		start;
	char	*word;
	char	*expanded;

	start = *i;
	while (input[*i] && input[*i] != ' '
		&& !is_separator(input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	if (*i == start)
		return (NULL);
	word = ft_substr(input, start, *i - start);
	if (!word)
		return (NULL);
	expanded = expand_variables(word, shell);
	free(word);
	return (expanded);
}

void	handle_word_token(t_token_context *context)
{
	char	*expanded;
	t_token	*last_token;
	char	*new_value;

	expanded = extract_and_expand_word(context->input, context->i,
			context->shell);
	if (!expanded)
		return ;
	if (!context->had_whitespace)
	{
		last_token = get_last_token(*(context->tokens));
		if (last_token && last_token->type == TK_WORD)
		{
			new_value = ft_strjoin(last_token->value, expanded);
			free(last_token->value);
			if (!new_value)
			{
				free(expanded);
				return ;
			}
			last_token->value = new_value;
			free (expanded);
			return ;
		}
	}
	add_token_to_list(context->tokens, create_token(expanded, TK_WORD));
	free (expanded);
}
