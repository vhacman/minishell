/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:59:07 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Counts how many tokens are of type TK_WORD in a token list.
** Process:
** 1. Initialize a counter to 0.
** 2. Iterate through each token in the list.
** 3. If the token's type is TK_WORD, increment the counter.
** 4. Move to the next token until the list ends.
** 5. Return the total count of TK_WORD tokens found.
**
** Returns:
** - The number of TK_WORD tokens in the list.
*/
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

/*
** Converts a list of tokens into an array of argument strings.
** Process:
** 1. Count the number of TK_WORD tokens using count_word_tokens.
** 2. Allocate memory for an array of strings (count + 1 for NULL terminator).
** 3. Iterate through the token list:
**    - If the token type is TK_WORD, duplicate its value and store it in args.
** 4. Set the last element of the array to NULL.
** 5. Return the array of arguments.
*/
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
