/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_filtering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:03:34 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:04:55 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_redirection_file(t_token *tokens, t_token *curr)
{
	t_token	*prev;

	if (curr == tokens)
		return (0);
	prev = tokens;
	while (prev->next && prev->next != curr)
		prev = prev->next;
	if (prev && (prev->type == TK_OUT || prev->type == TK_APPEND
			|| prev->type == TK_IN || prev->type == TK_HEREDOC))
		return (1);
	return (0);
}

int	count_non_redirection_words(t_token *tokens)
{
	t_token	*curr;
	int		word_count;

	word_count = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_WORD && !is_redirection_file(tokens, curr))
			word_count++;
		curr = curr->next;
	}
	return (word_count);
}

char	**copy_args_to_array(t_token *tokens, char **args, int word_count)
{
	t_token	*curr;
	int		i;

	curr = tokens;
	i = 0;
	while (curr && i < word_count)
	{
		if (curr->type == TK_WORD)
		{
			if (!is_redirection_file(tokens, curr))
			{
				args[i] = ft_strdup(curr->value);
				if (!args[i])
				{
					while (--i >= 0)
						free(args[i]);
					free(args);
					return (NULL);
				}
				i++;
			}
		}
		curr = curr->next;
	}
	return (args);
}

char	**create_args_without_redirection(t_token *tokens)
{
	int		word_count;
	char	**args;

	word_count = count_non_redirection_words(tokens);
	if (word_count == 0)
		return (NULL);
	args = calloc(sizeof(char *), word_count + 1);
	if (!args)
		return (NULL);
	args = copy_args_to_array(tokens, args, word_count);
	if (!args)
		return (NULL);
	args[word_count] = NULL;
	return (args);
}
