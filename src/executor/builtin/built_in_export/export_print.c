/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:35:24 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:59:35 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** env_list_to_array
**
** This helper function converts a linked list of environment
** variables into an array of pointers.
** - Allocate an array of size 'size' to hold t_env pointers.
** - Iterate through the linked list up to 'size' elements.
** - For each node, store its pointer in the array.
** - Return the filled array of environment variable pointers.
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
** print_export_sorted
**
** This function prints the environment variables in sorted order.
** - Get the total number of environment variables with
**   env_list_size().
** - Convert the linked list of variables into an array using
**   env_list_to_array().
** - If the list is empty (size == 0), return immediately.
** - Sort the array with selection_sort_env().
** - Print the sorted variables recursively using
**   print_exported_recursive().
** - Free the temporary array before returning.
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
** print_exported_recursive
**
** This function prints exported environment variables from
** an array recursively.
** - Base case: if index i is greater than or equal to size,
**   stop recursion.
** - Get the current node at arr[i].
** - If the variable is marked as exported:
**     * Print "declare -x " followed by the key.
**     * If the variable has a value, print it in quotes.
**     * Print a newline at the end.
** - Recursively call the function with the next index (i + 1).
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
