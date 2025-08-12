/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_string_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:01:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:12:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static int	skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

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

static int	skip_prefix(char *str)
{
	int	i;

	i = skip_whitespace(str);
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (i);
}

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
