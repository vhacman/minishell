/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:18:27 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:08:45 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../include/minishell.h"

/*
** Counts the total number of environment variable nodes
** in the linked list.
** 1. Initialize `env_count` to 0.
** 2. Traverse the linked list starting from `env`.
** 3. For each node encountered, increment `env_count`.
** 4. Continue until the end of the list (NULL).
** 5. Return the final count as a `size_t` value.
*/
size_t	count_env_nodes(t_env *env)
{
	size_t	env_count;

	env_count = 0;
	while (env)
	{
		env_count++;
		env = env->next;
	}
	return (env_count);
}

/*
** Appends a new environment node to the end of the list.
** 1. If the list is empty (`*env_list` is NULL), set
**    `*env_list` to `new_node` and return 1.
** 2. Otherwise, start from the head and iterate until
**    reaching the last node (where `next` is NULL).
** 3. Set the `next` pointer of the last node to `new_node`.
** 4. Return 1 to indicate that the node was successfully
**    added.
*/
int	add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*current;

	if (!*env_list)
	{
		*env_list = new_node;
		return (1);
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (1);
}

/*
** Updates the value and export status of an environment node.
** 1. If `node` is NULL, return 0 (update failed).
** 2. Free the current value stored in the node.
** 3. If `new_value` is provided:
**    - Duplicate it and assign it to `node->value`.
**    - If duplication fails, return 0.
** 4. If `new_value` is NULL, set `node->value` to NULL.
** 5. Update the `exported` flag to `exported_flag`.
** 6. Return 1 to indicate a successful update.
*/
int	update_env_node(t_env *node, char *new_value, int exported_flag)
{
	if (!node)
		return (0);
	free(node->value);
	if (new_value)
		node->value = ft_strdup(new_value);
	else
		node->value = NULL;
	if (new_value && !node->value)
		return (0);
	node->exported = exported_flag;
	return (1);
}

/*
** Counts the number of nodes in the environment list.
** 1. Initialize `count` to 0.
** 2. Traverse the linked list `env`:
**    - Increment `count` for each node.
** 3. Return the final count after reaching the end of the list.
*/
int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/*
** Searches for an environment variable node by key.
** 1. Iterate through the linked list `env_list`.
** 2. For each node, compare its `key` with the given `key`
**    using `ft_strcmp`.
**    - If they match, return the current node.
** 3. If no match is found after reaching the end of the list,
**    return NULL.
*/
t_env	*find_env_node(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}
