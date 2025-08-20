/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:34:31 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:03:25 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_token	*match_redirection(t_token *curr, int *redirect_type,
					bool input_only)
{
	if (input_only)
	{
		if (curr->type == TK_IN || curr->type == TK_HEREDOC)
		{
			*redirect_type = curr->type;
			return (curr);
		}
	}
	else
	{
		if (curr->type == TK_OUT || curr->type == TK_APPEND)
		{
			*redirect_type = curr->type;
			return (curr);
		}
	}
	return (NULL);
}

t_token	*find_redirection_token(t_token *tokens, int *redirect_type,
				bool input_only)
{
	t_token	*curr;
	t_token	*match;

	curr = tokens;
	while (curr)
	{
		match = match_redirection(curr, redirect_type, input_only);
		if (match)
			return (match);
		curr = curr->next;
	}
	*redirect_type = 0;
	return (NULL);
}

char	*get_filename_from_next_token(t_token *redirect_token)
{
	t_token	*next_token;

	if (!redirect_token || !redirect_token->next)
		return (NULL);
	next_token = redirect_token->next;
	if (next_token->type != TK_WORD)
		return (NULL);
	return (ft_strdup(next_token->value));
}
