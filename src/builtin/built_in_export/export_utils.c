/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:33:27 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 16:53:20 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_env	**env_list_to_array(t_env *env, int size)
{
	t_env	**array;
	int		i;

	array = calloc(sizeof(t_env *), size);
	i = 0;
	while (env && i < size)
	{
		array[i++] = env;
		env = env->next;
	}
	return (array);
}

void	print_export_sorted(t_env *env_list)
{
	int		size;
	t_env	**arr;

	size = env_list_size(env_list);
	arr = env_list_to_array(env_list, size);
	if (size == 0)
		return ;
	selection_sort_env(arr, size);
	print_exported_recursive(arr, size, 0);
	free(arr);
}

/*
** is_valid_identifier - Check if a string is a valid identifier (up to '=')
** Returns 1 if:
**   - str is not empty
**   - the first character is a letter (A–Z, a–z) or underscore (‘_’)
**   - all subsequent characters before an optional ‘=’ are letters,
**		digits, or underscore
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
