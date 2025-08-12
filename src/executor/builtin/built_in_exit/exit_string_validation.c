/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_string_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:01:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:33:51 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** Counts how many leading whitespace characters are in a string.
** 1. Initialize index `i` to 0.
** 2. While the current character exists and is either a space
**    or a tab, increment `i`.
** 3. Return the total number of whitespace characters skipped.
*/
int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

/*
** Checks if converting a numeric string to a long integer
** would cause an overflow.
** 1. Initialize `result` to 0.
** 2. Loop through consecutive digits starting at index `i`:
**    - Multiply `result` by 10 and add the current digit's
**      numeric value.
**    - If `sign` is positive and `result` exceeds LONG_MAX,
**      return 1 (overflow detected).
**    - If `sign` is negative and `result` exceeds
**      LONG_MAX + 1 (absolute range for LONG_MIN),
**      return 1 (overflow detected).
** 3. If no overflow occurs, return 0.
*/
static int	is_overflow(char *str, int i, int sign)
{
	unsigned long	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > (unsigned long)LONG_MAX)
			return (1);
		if (sign == -1 && result > (unsigned long)LONG_MAX + 1UL)
			return (1);
		i++;
	}
	return (0);
}

/*
** Validates if a string can be safely converted to a long
** without overflow.
** 1. If `str` is NULL or empty, return 1 (invalid input).
** 2. Skip leading whitespace using `skip_whitespace`.
** 3. Set the default sign to positive (1).
** 4. If the current character is '+' or '-', update the sign
**    accordingly and advance the index.
** 5. If there are no digits after an optional sign, return 1
**    (invalid number).
** 6. Call `is_overflow` to check if the numeric part exceeds
**    the valid range for a long integer.
** 7. Return the result of `is_overflow` (1 if overflow,
**    0 if safe).
*/
int	check_atol_conversion(char *str)
{
	int	i;
	int	sign;

	if (!str || str[0] == '\0')
		return (1);
	i = skip_whitespace(str);
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0' || str[i] < '0' || str[i] > '9')
		return (1);
	return (is_overflow(str, i, sign));
}

/*
** Skips leading whitespace and an optional sign in a string.
** 1. Use `skip_whitespace` to move past any spaces or tabs,
**    storing the new index in `i`.
** 2. If the next character is '+' or '-', increment `i` to
**    skip the sign.
** 3. Return the updated index position.
*/
static int	skip_prefix(char *str)
{
	int	i;

	i = skip_whitespace(str);
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (i);
}

/*
** Checks if a string represents a valid numeric value.
** 1. If `str` is NULL or empty, return 0 (not numeric).
** 2. Skip any leading whitespace and optional sign using
**    `skip_prefix`.
** 3. If the string ends immediately after the prefix, return
**    0 (no digits found).
** 4. Initialize `has_digits` to 0.
** 5. Iterate through the characters:
**    - If a digit is found, set `has_digits` to 1 and
**      continue.
**    - If a space or tab is found, skip remaining whitespace
**      and break.
**    - If any other character is found, return 0 (invalid).
** 6. Return `has_digits` (1 if at least one digit was found,
**    0 otherwise).
*/
int	is_numeric(char *str)
{
	int	i;
	int	has_digits;

	if (!str || str[0] == '\0')
		return (0);
	i = skip_prefix(str);
	if (str[i] == '\0')
		return (0);
	has_digits = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			has_digits = 1;
			i++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
		{
			i = skip_whitespace(str);
			break ;
		}
		else
			return (0);
	}
	return (has_digits);
}
