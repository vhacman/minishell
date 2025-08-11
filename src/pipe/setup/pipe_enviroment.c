/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_enviroment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:53:28 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 15:10:09 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*create_key_value_string(t_env *env)
{
	size_t	key_length;
	size_t	value_length;
	char	*key_value_string;

	key_length = ft_strlen(env->key);
	value_length = 0;
	if (env->value)
		value_length = ft_strlen(env->value);
	key_value_string = (char *)malloc(key_length + 1 + value_length + 1);
	if (!key_value_string)
		return (NULL);
	ft_memcpy(key_value_string, env->key, key_length);
	key_value_string[key_length] = '=';
	if (env->value)
		ft_memcpy(key_value_string + key_length + 1, env->value, value_length);
	key_value_string[key_length + 1 + value_length] = '\0';
	return (key_value_string);
}

char	**build_envp_from_list(t_env *env)
{
	size_t	env_count;
	char	**environment_array;
	size_t	array_index;

	env_count = count_env_nodes(env);
	environment_array = (char **)malloc(sizeof(char *) * (env_count + 1));
	if (!environment_array)
		return (NULL);
	array_index = 0;
	while (env)
	{
		environment_array[array_index] = create_key_value_string(env);
		if (!environment_array[array_index])
		{
			environment_array[array_index] = NULL;
			free_args_array(environment_array);
			return (NULL);
		}
		array_index++;
		env = env->next;
	}
	environment_array[array_index] = NULL;
	return (environment_array);
}
