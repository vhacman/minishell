/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:03:09 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:10:35 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../include/minishell.h"

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

int	set_env_value(t_env **envp, const char *key, const char *value)
{
	if (update_env_value_if_exists(*envp, key, value) == 0)
		return (0);
	return (append_env_value_if_missing(envp, key, value));
}
