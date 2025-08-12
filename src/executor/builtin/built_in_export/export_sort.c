/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:24:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:35:06 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** Finds the index of the smallest `key` in a `t_env *` array.
** 1. Initialize `min_idx` as the `start` index.
** 2. Loop from `start + 1` to the end of the array:
**    - Compare each `key` with the current minimum key
**      using `ft_strcmp`.
**    - If a smaller key is found, update `min_idx`.
** 3. Return the index of the lexicographically smallest key.
*/
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

/*
** Swaps two elements in an array of `t_env *`.
** This operation only swaps the array elements, not the
** linked list nodes themselves.
*/
static void	swap_env(t_env **arr, int i, int j)
{
	t_env	*temp;

	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

/*
** Sorts an array of environment variable pointers by key
** using the selection sort algorithm.
** 1. Iterate through the array from index 0 to `size - 2`.
** 2. For each position `i`, find the index of the smallest
**    key (lexicographically) from `i` to the end using
**    `find_min_index`.
** 3. If the smallest element is not already at position `i`,
**    swap it with the element at `i` using `swap_env`.
** 4. Continue until the array is sorted.
*/
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
