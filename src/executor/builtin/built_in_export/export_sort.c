/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:24:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:11:41 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static int	find_min_index(t_env **arr, int size, int start)
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

static void	swap_env(t_env **arr, int i, int j)
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
