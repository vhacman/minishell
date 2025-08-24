/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:50:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:39:23 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** count_valid_args
**
** This function counts the number of valid arguments in a
** token list.
** - Iterate through each token in the list.
** - If the token type is TK_WORD:
**     * Check if it is not the target of an input redirection
**       using is_input_redir_target().
**     * If not a redirection target, increase the count.
** - Return the total number of valid argument tokens found.
*/
int	count_valid_args(t_token *tokens)
{
	t_token		*curr;
	int			word_count;

	word_count = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_WORD)
		{
			if (!is_input_redir_target(tokens, curr))
				word_count++;
		}
		curr = curr->next;
	}
	return (word_count);
}

/*
** extract_raw_word
**
** This function extracts a raw word starting at index *i.
** - Save the starting position.
** - Advance *i while the current character:
**     * is not null,
**     * is not a space,
**     * is not a separator (like |, <, >),
**     * is not a single or double quote.
** - Calculate the length of the word.
** - If length is 0 or less, return NULL (no word found).
** - Otherwise, return a new substring from start to *i.
*/
char	*extract_raw_word(const char *input, int *i)
{
	int		start;
	char	*word;
	int		len;

	start = *i;
	while (input[*i] && input[*i] != ' ' && !is_separator(input[*i])
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	len = *i - start;
	if (len <= 0)
		return (NULL);
	word = ft_substr(input, start, *i - start);
	return (word);
}

char	*unescape_unquoted(const char *s)
{
	int		i;
	int		j;
	char	*out;

	if (!s)
		return (NULL);
	out = calloc(ft_strlen(s) + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
		{
			out[j] = s[i + 1];
			i += 2;
		}
		else
			out[j] = s[i++];
		j++;
	}
	return (out);
}

