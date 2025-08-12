/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:33:27 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:34:31 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** Checks if a string is a valid shell variable identifier.
** 1. Must not be NULL or empty.
** 2. First character must be a letter or underscore.
** 3. Following characters (before '=') must be letters,
**    digits, or underscores.
** 1. Return 0 if the string is NULL or empty.
** 2. Verify the first character is alphabetic or '_'.
** 3. Iterate through the remaining characters until '='
**    or the end of the string, checking that each one is
**    alphanumeric or '_'.
** 4. Return 1 if all checks pass, otherwise return 0.
*/
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
** Extracts the key (variable name) from an environment
** string in the form "KEY=VALUE".
** 1. Search for the first occurrence of '=' in the string.
** 2. If '=' is not found, return a duplicate of the whole
**    string (it has no value part).
** 3. If '=' is found, calculate the length of the key as
**    the distance from the start of the string to '='.
** 4. Return a substring containing only the key portion.
*/
char	*extract_key(char *str)
{
	char	*eq_position;
	int		key_len;

	eq_position = ft_strchr(str, '=');
	if (!eq_position)
		return (ft_strdup(str));
	key_len = eq_position - str;
	return (ft_substr(str, 0, key_len));
}

/*
** Extracts the value part from an environment string in
** the form "KEY=VALUE".
** 1. Locate the first '=' character in the input string.
** 2. If no '=' is found, return NULL (the variable has no value).
** 3. Duplicate and return the substring starting right after
**    the '=' character, which represents the value.
*/
char	*extract_value(char *str)
{
	char	*eq_position;

	eq_position = ft_strchr(str, '=');
	if (!eq_position)
		return (NULL);
	return (ft_strdup(eq_position + 1));
}
