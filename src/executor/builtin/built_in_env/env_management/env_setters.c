/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:03:09 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:33:28 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../include/minishell.h"

/*
** Retrieves the value of an environment variable by key.
**
** Steps:
** 1. Traverse the environment linked list starting from `env`.
** 2. For each node, compare its `key` with the provided `key`
**    using `ft_strcmp`.
**    - If a match is found, return the variable's `value`.
** 3. If no match is found after reaching the end of the list,
**    return NULL.
*/
char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*
** Updates the value of an existing environment variable
** if it is found in the environment list.
**
** Steps:
** 1. Search for the variable by `key` using `find_env_node`.
**    - If not found, return 1 (no update performed).
** 2. Call `update_env_node` to change the value while keeping
**    the same `exported` flag.
**    - If the update succeeds, return 0.
**    - If it fails (e.g., allocation error), return 1.
*/
int	update_env_value_if_exists(t_env *envp, const char *key, const char *value)
{
	t_env	*node;

	node = find_env_node(envp, (char *)key);
	if (!node)
		return (1);
	if (update_env_node(node, (char *)value, node->exported))
		return (0);
	return (1);
}

/*
** Appends a new environment variable if it does not already exist.
**
** Steps:
** 1. Check if a variable with the given `key` exists in the
**    environment list using `find_env_node`.
**    - If it exists, return 0 (no action needed).
** 2. Create a new environment node with `create_env_node`,
**    marking it as exported.
**    - If creation fails, return 1 (error).
** 3. Add the new node to the environment list using
**    `add_env_node`.
**    - If successful, return 0.
**    - Otherwise, return 1 (error).
*/
int	append_env_value_if_missing(t_env **envp, const char *key,
									const char *value)
{
	t_env	*exists;
	t_env	*node;

	exists = find_env_node(*envp, (char *)key);
	if (exists)
		return (0);
	node = create_env_node((char *)key, (char *)value, 1);
	if (!node)
		return (1);
	if (add_env_node(envp, node))
		return (0);
	return (1);
}

/*
** Sets an environment variable to a specified value.
** 1. Attempt to update the value of an existing variable
**    using `update_env_value_if_exists`.
**    - If it returns 0, the variable was updated successfully,
**      so return 0.
** 2. If the variable does not exist, append it to the
**    environment list using `append_env_value_if_missing`.
** 3. Return the result of the append operation.
*/
int	set_env_value(t_env **envp, const char *key, const char *value)
{
	if (update_env_value_if_exists(*envp, key, value) == 0)
		return (0);
	return (append_env_value_if_missing(envp, key, value));
}
