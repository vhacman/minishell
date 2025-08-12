/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:17:14 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:44:33 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Removes an environment variable node from a linked list based on its key.
**
** The function traverses the linked list starting from *env_list_ptr and
** compares each node's key with the provided 'key'. When a match is found:
**   - If the node is not the head, link the previous node to the next node.
**   - If the node is the head, update the list head to the next node.
**   - Free the matched node's memory.
*/
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
			return (free_env_node(current), 1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

/*
** Validates and removes an environment variable from the list.
**
** The function first checks if 'arg' is a valid identifier for an environment
** variable. If invalid, it prints an error message to stderr and returns 1.
** If valid, it removes the variable from the environment list by calling
** remove_env_node().
*/
static int	process_unset_arg(t_env **env_list_ptr, char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		return (1);
	}
	return (remove_env_node(env_list_ptr, arg), 0);
}

/*
** Removes environment variables from the environment list.
**
** Iterates over the provided arguments (starting from args[1]) and calls
** process_unset_arg() for each variable name. Tracks if any invalid
** identifiers are encountered.
*/
int handle_unset(t_env **env_list, char **args)
{
	int	arg_index;
	int	status;
	
	if (!env_list || !args || !args[1])
		return (0);
	arg_index = 1;
	status = 0;
	while (args[arg_index])
	{
		if (process_unset_arg(env_list, args[arg_index]) != 0)
			status = 1;
		arg_index++;
	}
	return (status);
}
