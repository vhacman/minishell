/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:45:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:33:09 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../include/minishell.h"

/*
** Allocates and initializes a new environment variable node.
** 1. Allocate memory for a `t_env` structure and zero it out.
**    If allocation fails, return NULL.
** 2. Duplicate the `key` string and store it in the node.
**    If duplication fails, free the node and return NULL.
** 3. If `value` is provided, duplicate and store it.
**    If duplication fails, free the key and node, then return NULL.
**    If no value is provided, set the node's value to NULL.
** 4. Set the `exported` flag to indicate if the variable
**    should be included in the environment.
** 5. Initialize `next` to NULL to mark the end of the list.
** 6. Return the pointer to the newly created node.
*/
t_env	*create_env_node(char *key, char *value, int exported)
{
	t_env	*new_node;

	new_node = calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (free(new_node), NULL);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (free(new_node->key), free(new_node), NULL);
	}
	else
		new_node->value = NULL;
	new_node->exported = exported;
	new_node->next = NULL;
	return (new_node);
}

/*
** Converts a single environment string into a `t_env`
** linked list node.
** 1. Extract the key portion from `env_entry` using
**    `extract_key`.
** 2. Extract the value portion from `env_entry` using
**    `extract_value`.
** 3. If the key extraction fails, return NULL because a
**    valid environment variable must have a key.
** 4. Create a new environment node with `create_env_node`,
**    marking it as exported (last argument = 1).
** 5. Free the temporary `key` and `value` strings after
**    creating the node, since the node will store its own
**    copies.
** 6. Return the created node.
*/
static t_env	*process_env_entry(char *env_entry)
{
	t_env	*new;
	char	*key;
	char	*value;

	key = extract_key(env_entry);
	value = extract_value(env_entry);
	if (!key)
		return (NULL);
	new = create_env_node(key, value, 1);
	free(key);
	if (value)
		free(value);
	return (new);
}

/*
** Creates a linked list of environment variables from
** an array of strings.
** 1. Initialize `head` and `tail` pointers to NULL.
** 2. Loop through each string in `env_entries`:
**    - Process the string into a `t_env` node using
**      `process_env_entry`.
**    - If creation fails, free the list created so far
**      and return NULL.
**    - If the list is empty, set `head` to the new node.
**      Otherwise, append the new node after `tail`.
**    - Update `tail` to point to the new node.
** 3. Return the head of the newly created linked list.
*/
t_env	*copy_env_entries(char **env_entries)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new;

	head = NULL;
	tail = NULL;
	while (*env_entries)
	{
		new = process_env_entry(*env_entries);
		if (!new)
			return (free_env_list(head), NULL);
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		env_entries++;
	}
	return (head);
}
