/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:03:09 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 14:34:19 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int set_env_value(t_env **envp, const char *key, const char *value)
{
	t_env *cur;
	t_env *last;
	t_env *node;

	cur = *envp;
	last = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (update_env_node(cur, (char *)value, cur->exported))
				return (0);
			else
				return (1);
		}
		last = cur;
		cur = cur->next;
	}
	node = create_env_node((char *)key, (char *)value, 1);
	if (!node)
		return (1);
	if (last)
		last->next = node;
	else
		*envp = node;
	return (0);
}

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
