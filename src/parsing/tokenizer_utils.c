/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:52:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 16:18:39 by vhacman          ###   ########.fr       */
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
	int	start_i;

	start_i = *i;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (*i > start_i)
		*had_whitespace = 1;
	return (str[*i] != '\0');
}
