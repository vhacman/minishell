/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:52:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 12:50:11 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	skip_whitespace_and_check(const char *str, int *i, int *had_whitespace)
{
	int	skipped;

	skipped = skip_whitespace(str + *i);
	if (skipped > 0)
		*had_whitespace = 1;
	*i += skipped;
	return (str[*i] != '\0');
}
