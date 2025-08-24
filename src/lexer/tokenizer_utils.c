/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:52:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:13:45 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** only_spaces
**
** This function checks if a string contains only spaces or tabs.
** - Iterate through each character in the string.
** - If any character is not a space (' ') and not a tab ('\t'),
**   return 0 (false).
** - If the loop finishes without finding other characters,
**   return 1 (true).
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
** is_separator
**
** This function checks if a character is a token separator.
** - Returns 1 if the character is '|', '<', or '>'.
** - Returns 0 otherwise.
*/
int	is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
** skip_whitespace_and_check
**
** This function skips whitespace in the input string and checks
** if more characters remain.
** - It calls skip_whitespace() starting from the current index.
** - If at least one space was skipped, set *had_whitespace to 1.
** - The index *i is updated to the new position after skipping.
** - Returns 1 if the string has more characters to read,
**   or 0 if the end of the string is reached.
*/
int	skip_whitespace_and_check(const char *str, int *i, int *had_whitespace)
{
	int	skipped;

	skipped = skip_whitespace(str + *i);
	if (skipped > 0)
		*had_whitespace = 1;
	*i += skipped;
	return (str[*i] != '\0');
}
