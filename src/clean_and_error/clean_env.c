/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:21:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 15:32:33 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Frees all nodes in a linked list of environment variables.
**
** Steps:
** 1. Loop through each node in the list:
**    - Store the pointer to the next node in `tmp`.
**    - Free the `key` string if it exists.
**    - Free the `value` string if it exists.
**    - Free the node structure itself.
** 2. Move to the next node using `tmp` and repeat until
**    the list is fully freed.
*/
void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

/*
** Frees a single environment variable node.
**
** Steps:
** 1. If the given node is NULL, do nothing.
** 2. Use `free_parts` to free the key and value strings.
** 3. Free the node structure itself.
*/
void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free_parts(node->key, node->value, NULL);
	free(node);
}
