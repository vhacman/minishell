/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:35:24 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 12:51:42 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	handle_existing_node(t_env *node, char *value)
{
	if (value)
		update_env_node(node, value, 1);
	else
		node->exported = 1;
	return (0);
}

static int	handle_new_node(t_env **env_list_ptr, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value, 1);
	if (!new_node || !add_env_node(env_list_ptr, new_node))
		return (1);
	return (0);
}

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
	return (free(key), free(value), status);
}

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
** handle_export:
**   argv: array di stringhe dei parametri (argv[0] == "export")
**   env_list: puntatore alla testa della lista t_env* del minishell
** Ritorna 0 se va tutto bene, 1 in caso di identificatori non validi
*/
int	handle_export(t_env **env_list, char **argv)
{
	int	return_code;

	return_code = export_variable(env_list, argv);
	return (return_code);
}
