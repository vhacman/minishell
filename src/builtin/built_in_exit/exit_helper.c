/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:01:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/06 15:03:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


/*
** Returns 1 if the string is not a valid numeric value or overflows a long.
** Accepts optional leading '+' or '-' sign.
*/
int	check_numeric_overflow(char *str)
{
	int			i;
	int			sign;
	unsigned long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
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


/*
** is_numeric - Checks if a string represents a valid numeric format.
** - Handles leading/trailing whitespace by skipping it
** - Allows optional + or - sign
** - Requires at least one digit
** - Does NOT check for overflow (that's handled separately)
** 
** This matches bash behavior for format checking.
*/
int	is_numeric(char *str)
{
	int	i;
	int	has_digits;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	has_digits = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			has_digits = 1;
			i++;
		}
		else if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			break;
		}
		else
			return (0);
	}
	return (has_digits);
}
