/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:35:24 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:11:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

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

void	print_exported_recursive(t_env **arr, int size, int index)
{
	t_env	*node;

	node = arr[index];
	if (index >= size)
		return ;
	if (node->exported)
	{
		ft_printf("declare -x %s", node->key);
		if (node->value)
			ft_printf("=\"%s\"", node->value);
		ft_printf("\n");
	}
	print_exported_recursive(arr, size, index + 1);
}
