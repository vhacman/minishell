/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:26:14 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** has_unclosed_quotes
**
** This function checks if a string ends with unclosed quotes.
** - It loops through each character of the string.
** - If inside double quotes, a backslash followed by another char
**   is skipped to handle escape sequences.
** - If a single quote is found and not inside double quotes, toggle
**   the single_open flag.
** - If a double quote is found and not inside single quotes, toggle
**   the double_open flag.
** - At the end, return true if either single or double quotes are
**   still open (unclosed).
*/
int	has_unclosed_quotes(const char *str)
{
	int		i;
	int		single_open;
	int		double_open;

	i = 0;
	single_open = 0;
	double_open = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && double_open)
		{
			i += 2;
			continue;
		}
		if (str[i] == '\'' && !double_open)
			single_open = !single_open;
		else if (str[i] == '"' && !single_open)
			double_open = !double_open;
		i++;
	}
	return (single_open || double_open);
}

/*
** process_escape_char
**
** This helper function converts escape characters into their
** real character values.
** - 'n' becomes newline '\n'.
** - 't' becomes tab '\t'.
** - 'r' becomes carriage return '\r'.
** - '\\' becomes a backslash.
** - '"' becomes a double quote.
** - '\'' becomes a single quote.
** - Any other character is returned unchanged.
*/
static char	process_escape_char(char c)
{
	if (c == 'n')
		return ('\n');
	if (c == 't')
		return ('\t');
	if (c == 'r')
		return ('\r');
	if (c == '\\')
		return ('\\');
	if (c == '"')
		return ('"');
	if (c == '\'')
		return ('\'');
	return (c);
}

/*
** process_escaped_content
**
** This helper function processes a substring and resolves escape
** sequences inside it.
** - It allocates memory for a new string of length 'len'.
** - It loops through the substring from 'start' to 'start + len'.
** - If a backslash is found and another char follows:
**     * Convert the escaped character using process_escape_char().
**     * Skip both characters.
** - Otherwise, copy the current character as it is.
** - The result string is null-terminated and returned.
** - Returns NULL if memory allocation fails.
*/
static char	*process_escaped_content(const char *str, int start, int len)
{
	char	*result;
	int		i;
	int		j;

	result = calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[start + i] == '\\' && i + 1 < len)
		{
			result[j] = process_escape_char(str[start + i + 1]);
			i += 2;
		}
		else
		{
			result[j] = str[start + i];
			i++;
		}
		j++;
	}
	return (result);
}

/*
** find_closing_quote
**
** This helper function searches for the closing quote in a string.
** - It starts scanning from the given index 'start'.
** - If the current character is a backslash inside double quotes,
**   skip the backslash and the next character (to handle escapes).
** - Otherwise, move to the next character normally.
** - If the matching closing quote is found, return its index.
** - If no closing quote exists, return -1 to signal failure.
*/
static int	find_closing_quote(const char *str, int start, char quote_char)
{
	int	i;

	i = start;
	while (str[i] && str[i] != quote_char)
	{
		if (str[i] == '\\' && str[i + 1] && quote_char == '"')
			i += 2;
		else
			i++;
	}
	if (str[i] != quote_char)
		return (-1);
	return (i);
}

/*
** extract_quoted_content
**
** This function extracts the content inside quotes from a string.
** - It starts scanning at the current index given by *index.
** - If the current char is the opening quote, skip it.
** - Find the matching closing quote using find_closing_quote().
** - If no closing quote is found, move index to the end of the
**   string and return NULL.
** - If the quote is double ("), process escapes inside the content.
** - If the quote is single ('), copy the content directly.
** - Update *index to the position after the closing quote.
** - Return the extracted substring (allocated), or NULL on error.
*/
char	*extract_quoted_content(const char *str, int *index, char quote_char)
{
	int		start;
	int		end;
	char	*quoted;
	int		i;

	i = *index;
	if (str[i] == quote_char)
		i++;
	start = i;
	end = find_closing_quote(str, start, quote_char);
	if (end == -1)
	{
		*index = ft_strlen(str);
		return (NULL);
	}
	if (quote_char == '"')
		quoted = process_escaped_content(str, start, end - start);
	else
		quoted = ft_substr(str, start, end - start);
	*index = end + 1;
	return (quoted);
}
