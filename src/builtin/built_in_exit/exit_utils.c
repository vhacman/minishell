/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:01:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 19:20:02 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Skips leading whitespace and sign.
** Returns the index of the first character after optional sign.
*/
static int	skip_leading_whitespace_and_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (i);
}

/*
** Checks digits followed by optional space.
** Returns 1 if the string contains at least one digit and
** any remaining characters are only whitespace.
*/
static int	has_only_digits_and_trailing_whitespace(char *str, int start)
{
	int	i;
	int	has_digits;

	i = start;
	has_digits = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		has_digits = 1;
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (0);
	return (has_digits);
}

/*
** Returns 1 if str is a valid numeric string.
** Uses helper functions to modularize whitespace/sign and digit check.
*/
int	is_numeric(char *str)
{
	int	start;

	if (!str || str[0] == '\0')
		return (0);
	start = skip_leading_whitespace_and_sign(str);
	if (str[start] == '\0')
		return (0);
	return (has_only_digits_and_trailing_whitespace(str, start));
}

/*
** parse_sign_and_index - Detects the sign and returns the start index.
** Sets sign to -1 if negative, otherwise 1.
*/
int	parse_sign_and_index(char *str, int *sign)
{
	int	i;

	i = 0;
	*sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

/*
** check_numeric_overflow - Checks if a numeric string exceeds long limits.
** Returns 1 if overflow or invalid format is detected, 0 otherwise.
*/
int	check_numeric_overflow(char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	result = 0;
	i = parse_sign_and_index(str, &sign);
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > LONG_MAX)
			return (1);
		if (sign == -1 && result > (unsigned long)LONG_MAX + 1)
			return (1);
		i++;
	}
	return (0);
}
