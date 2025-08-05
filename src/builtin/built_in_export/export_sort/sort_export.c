/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:24:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 19:25:09 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	find_min_index(t_env **arr, int size, int start)
{
	int	min_idx;
	int	i;

	min_idx = start;
	i = start + 1;
	while (i < size)
	{
		if (ft_strcmp(arr[i]->key, arr[min_idx]->key) < 0)
			min_idx = i;
		i++;
	}
	return (min_idx);
}

void	swap_env(t_env **arr, int i, int j)
{
	t_env	*temp;

	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void	selection_sort_env(t_env **arr, int size)
{
	int	i;
	int	min_idx;

	i = 0;
	while (i < size - 1)
	{
		min_idx = find_min_index(arr, size, i);
		if (min_idx != i)
			swap_env(arr, i, min_idx);
		i++;
	}
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
