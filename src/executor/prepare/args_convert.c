/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:20:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	count_word_tokens(t_token *tokens)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_WORD)
			count++;
		curr = curr->next;
	}
	return (count);
}

char	**convert_tokens_to_args(t_token *tokens)
{
	int		count;
	char	**args;
	t_token	*curr;
	int		i;

	i = 0;
	count = count_word_tokens(tokens);
	args = calloc(sizeof(char *), (count + 1));
	if (!args)
		return (NULL);
	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_WORD)
			args[i++] = ft_strdup(curr->value);
		curr = curr->next;
	}
	args[i] = NULL;
	return (args);
}

