/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:52:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:14:07 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Checks if a string contains only spaces or tabs.
** 1. Iterate through each character of the string.
** 2. If a character is not a space or tab, return 0.
** 3. If the loop completes, the string contains only spaces/tabs.
*/
int	only_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

/*
** Checks if a character is a command separator.
** 1. Compare `c` against '|', '<', and '>'.
** - 1 if `c` is a separator character.
** - 0 otherwise.
*/
int	is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
** Skips whitespace in the input string and checks if any
** was encountered.
** 1. Call `skip_whitespace` starting from the current index
**    (`str + *i`) to count how many whitespace characters
**    to skip.
** 2. If any whitespace was skipped (`skipped > 0`), set
**    `*had_whitespace` to 1.
** 3. Advance `*i` by the number of skipped characters.
** 4. Return 1 if the current character is not the null
**    terminator, otherwise return 0.
*/
int	skip_whitespace_and_check(const char *str, int *i, int *had_whitespace)
{
	int skipped;

	skipped = skip_whitespace(str + *i);
	if (skipped > 0)
		*had_whitespace = 1;
	*i += skipped;
	return (str[*i] != '\0');
}
