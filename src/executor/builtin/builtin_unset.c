/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:17:14 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 11:51:35 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	remove_env_node(t_env **env_list_ptr, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env_list_ptr || !*env_list_ptr || !key)
		return (0);
	current = *env_list_ptr;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list_ptr = current->next;
			free_env_node(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

static int	process_unset_arg(t_env **env_list_ptr, char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		return (1);
	}
	remove_env_node(env_list_ptr, arg);
	return (0);
}

int	unset_variable(t_env **env_list_ptr, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args[1])
		return (0);
	while (args[i])
	{
		if (process_unset_arg(env_list_ptr, args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}

int	handle_unset(t_env **env_list, char **argv)
{
	int	return_code;

	return_code = unset_variable(env_list, argv);
	return (return_code);
}
