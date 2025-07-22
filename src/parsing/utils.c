/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:52:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 22:45:31 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	Checks if the string contains only space or tab characters.
**
**	How it works	Iterates through each character in str until '\0';
**			returns 0 immediately upon finding a non-space/tab.
**	Params:		str	- null‑terminated string to check
**	Returns:	1 if only spaces/tabs (or empty), 0 otherwise
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
**	Determines if a character is a shell separator ('|', '<', '>').
**
**	How it works	Compares c against separator characters.
**	Params:		c	- character to test
**	Returns:	1 if c is '|' or '<' or '>', 0 otherwise
*/
int	is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
**	Skips leading spaces/tabs and signals if any were skipped.
**
**	How it works	Saves original index, advances *i while str[*i]
					is space/tab;
					if index moved, sets *had_whitespace to 1.
**	Params:		str				- input string to scan
**				i				- pointer to parse index (updated)
**				had_whitespace	- pointer to flag for whitespace skip
**	Returns:	1 if next character is not '\0', 0 if end of string
*/
int	skip_whitespace_and_check(const char *str, int *i, int *had_whitespace)
{
	int	start_i;

	start_i = *i;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (*i > start_i)
		*had_whitespace = 1;
	return (str[*i] != '\0');
}
