/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:18:27 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:10:23 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../include/minishell.h"

size_t	count_env_nodes(t_env *env)
{
	size_t	env_count;
	t_env	*current_env;

	env_count = 0;
	current_env = env;
	while (current_env)
	{
		env_count++;
		current_env = current_env->next;
	}
	return (env_count);
}

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

t_env	*find_env_node(t_env *env_list, char *key)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
