/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:35:24 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:34:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** Updates an existing environment node when processing `export`.
** 1. If a `value` is provided:
**    - Call `update_env_node` to replace the existing value
**      and ensure the node is marked as exported.
** 2. If no `value` is provided:
**    - Simply set the `exported` flag to 1 without changing
**      the current value.
** 3. Always return 0 to indicate successful handling.
*/
static int	handle_existing_node(t_env *node, char *value)
{
	if (value)
		update_env_node(node, value, 1);
	else
		node->exported = 1;
	return (0);
}

/*
** Creates and adds a new environment variable node to the list.
** 1. Create a new environment node with `create_env_node`,
**    setting `exported` to 1.
** 2. If node creation fails or `add_env_node` fails to append
**    it to the list, return 1 (error).
** 3. Return 0 to indicate the new node was successfully added.
*/
static int	handle_new_node(t_env **env_list_ptr, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value, 1);
	if (!new_node || !add_env_node(env_list_ptr, new_node))
		return (1);
	return (0);
}

/*
** Processes a single argument passed to the `export` command.
** 1. Extract the key and value from the argument string
**    using `extract_key` and `extract_value`.
** 2. Initialize `status` to 0 (no error).
** 3. Validate the key with `is_valid_identifier`:
**    - If invalid, print an error message to stderr and set
**      `status` to 1.
** 4. If the key is valid:
**    - Search for an existing node in the environment list
**      using `find_env_node`.
**    - If found, update it via `handle_existing_node`.
**    - If not found, create and add a new node via
**      `handle_new_node`.
** 5. Free `key` and `value` before returning.
** 6. Return `status` (0 if success, 1 if error).
*/
static int	process_export_arg(t_env **env_list_ptr, char *arg)
{
	char	*key;
	char	*value;
	t_env	*node;
	int		status;

	key = extract_key(arg);
	value = extract_value(arg);
	status = 0;
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		status = 1;
	}
	else
	{
		node = find_env_node(*env_list_ptr, key);
		if (node)
			status = handle_existing_node(node, value);
		else
			status = handle_new_node(env_list_ptr, key, value);
	}
	return (free_parts(key, value, NULL), status);
}

/*
** Processes the `export` command arguments and updates
** the environment list accordingly.
** 1. Initialize `i` to 1 to skip the command name and
**    `status` to 0.
** 2. If no arguments are provided after "export":
**    - Call `print_export_sorted` to display all exported
**      variables in sorted order.
**    - Return 0 (no error).
** 3. Loop through each argument starting from index 1:
**    - Call `process_export_arg` for the current argument.
**    - If it returns a non-zero value, set `status` to 1
**      to indicate an error occurred for at least one arg.
** 4. Return `status`:
**    - 0 if all arguments were processed successfully.
**    - 1 if any argument failed to be processed.
*/
int	export_variable(t_env **env_list_ptr, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (!args[1])
	{
		print_export_sorted(*env_list_ptr);
		return (0);
	}
	while (args[i])
	{
		if (process_export_arg(env_list_ptr, args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}

/*
** Handles the `export` built-in command by delegating to
** the variable export logic.
** 1. Call `export_variable` with the given environment list
**    and argument array (`argv`).
** 2. Store its return value in `return_code`.
** 3. Return `return_code` to indicate the result of the
**    export operation.
*/
int	handle_export(t_env **env_list, char **argv)
{
	int	return_code;

	return_code = export_variable(env_list, argv);
	return (return_code);
}
