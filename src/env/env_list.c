/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:45:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 18:08:13 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
