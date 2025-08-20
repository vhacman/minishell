/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_enviroment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:53:28 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:10:37 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Creates a string in the format "key=value" from a `t_env` node.
**
** Parameters:
** - env: Pointer to the environment variable node.
**
** Process:
** 1. Concatenate the key with "=" and store it in `tmp`.
** 2. If a value exists:
**    - Concatenate `tmp` with the value.
**    - Free `tmp` after use.
** 3. If no value exists:
**    - Use `tmp` as the final string.
** 4. Return the resulting string or NULL if allocation fails.
**
** Returns:
** - Pointer to the allocated "key=value" string.
** - NULL if memory allocation fails.
*/
static char	*create_key_value_string(t_env *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	if (env->value)
	{
		result = ft_strjoin(tmp, env->value);
		free(tmp);
		if (!result)
			return (NULL);
	}
	else
		result = tmp;
	return (result);
}

/*
** Builds an environment array (`envp`) from a linked list of `t_env` nodes.
** Process:
** 1. Count the number of environment variables with `count_env_nodes`.
** 2. Allocate an array of `char *` large enough to store all entries
**    plus a NULL terminator.
** 3. Iterate through the list:
**    - Convert each node to "key=value" using `create_key_value_string`.
**    - Store each string in the array.
**    - If allocation fails, free all allocated strings and return NULL.
** 4. The last element of the array is set to NULL for `execve` compatibility.
*/
char	**build_envp_from_list(t_env *env)
{
	size_t	env_count;
	char	**environment_array;
	size_t	i;

	env_count = count_env_nodes(env);
	environment_array = calloc(env_count + 1, sizeof(*environment_array));
	if (!environment_array)
		return (NULL);
	i = 0;
	while (env)
	{
		environment_array[i] = create_key_value_string(env);
		if (!environment_array[i])
			return (free_args_array(environment_array), NULL);
		i++;
		env = env->next;
	}
	return (environment_array);
}
