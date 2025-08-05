/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:01:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 17:24:27 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
