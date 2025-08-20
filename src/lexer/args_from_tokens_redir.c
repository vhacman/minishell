/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_from_tokens_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:42:08 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 18:58:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_input_redir_target(t_token *tokens, t_token *curr)
{
	t_token	*prev;
	t_token	*temp;

	prev = NULL;
	temp = tokens;
	while (temp && temp != curr)
	{
		prev = temp;
		temp = temp->next;
	}
	if (prev && (prev->type == TK_IN || prev->type == TK_HEREDOC))
		return (1);
	return (0);
}

char	**create_args_without_input_redirection(t_token *tokens)
{
	t_token	*curr;
	int		word_count;
	char	**args;
	int		i;

	i = 0;
	word_count = count_valid_args(tokens);
	args = calloc(sizeof(char *), word_count + 1);
	if (!args)
		return (NULL);
	curr = tokens;
	while (curr && i < word_count)
	{
		if (curr->type == TK_WORD)
		{
			if (!is_input_redir_target(tokens, curr))
				args[i++] = ft_strdup(curr->value);
		}
		curr = curr->next;
	}
	args[i] = NULL;
	return (args);
}
