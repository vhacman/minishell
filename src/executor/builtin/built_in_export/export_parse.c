/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:33:27 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:11:58 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

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

char	*extract_value(char *str)
{
	char	*eq_position;

	eq_position = ft_strchr(str, '=');
	if (!eq_position)
		return (NULL);
	return (ft_strdup(eq_position + 1));
}
