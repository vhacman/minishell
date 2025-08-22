/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:55:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 15:29:58 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
