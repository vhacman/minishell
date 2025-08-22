/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 14:51:02 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
