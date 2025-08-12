/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:35:24 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:34:44 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** Converts an environment linked list into an array of
** `t_env *` pointers.
** 1. Allocate memory for an array of `t_env *` with the
**    given `size`, initializing all elements to NULL.
** 2. Iterate through the linked list:
**    - Assign each node pointer to the array in order.
**    - Increment `i` until all nodes are stored or `size`
**      is reached.
** 3. Return the populated array.
*/
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

/*
** Prints all exported environment variables in sorted order.
** 1. Get the number of environment nodes with
**    `env_list_size`.
** 2. Convert the linked list to an array of `t_env *` using
**    `env_list_to_array`.
** 3. If the list is empty (`size == 0`), return immediately.
** 4. Sort the array by key using `selection_sort_env`.
** 5. Print all exported variables in order using
**    `print_exported_recursive`.
** 6. Free the temporary array after printing.
*/
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
** Recursively prints all exported environment variables
** from a sorted array of `t_env` pointers.
** 1. If `i` is greater than or equal to `size`, stop
**    recursion (end of array reached).
** 2. Get the node at the current `index`.
** 3. If the node is marked as exported:
**    - Print "declare -x " followed by the key.
**    - If the node has a value, print it in quotes after '='.
**    - Print a newline.
** 4. Recursively call the function for the next index.
*/
void	print_exported_recursive(t_env **arr, int size, int i)
{
	t_env	*node;

	node = arr[i];
	if (i >= size)
		return ;
	if (node->exported)
	{
		ft_printf("declare -x %s", node->key);
		if (node->value)
			ft_printf("=\"%s\"", node->value);
		ft_printf("\n");
	}
	print_exported_recursive(arr, size, i + 1);
}
