/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:01:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/08 11:42:53 by vhacman          ###   ########.fr       */
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

static int ft_skip_whitespace(char *str)
{
	int	i;

	i = 0;
	while(str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

static int	ft_skip_prefix(char *str)
{
	int	i;

	i = ft_skip_whitespace(str);
	if(str[i] == '+' || str[i] == '-')
		i++;
	return (i);
}

int	is_numeric(char *str)
{
	int	i;
	int	has_digits;

	if(!str || str[0] == '\0')
		return (0);
	i = ft_skip_prefix(str);
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
			i = ft_skip_whitespace(str);
			break;
		}
		else
			return (0);
	}
	return (has_digits);
}
