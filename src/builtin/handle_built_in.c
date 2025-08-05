/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:48:12 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/28 11:26:30 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** handle_builtin - Dispatches execution of builtin shell commands.
**
** @args:  Array of strings representing the command and its arguments.
** @shell: Pointer to the main shell state structure.
**
** This function routes execution to the appropriate handler function
** based on the first string in `args` (the command name).
**
** Supported builtins and their handlers:
** - "pwd"    → handle_pwd()
** - "cd"     → handle_cd()
** - "exit"   → handle_exit()
** - "export" → handle_export()
** - "env"    → handle_env()
** - "unset"  → handle_unset()
** - "clear"  → handle_clear()
** - "echo"   → handle_echo()
**
** Behavior:
** - Calls the relevant function based on args[0].
** - Stores the return value in `result`.
** - Updates shell->exit_status with the command result.
**
** Return:
** - The result code from the called builtin handler.
** - 0 if the command was valid and successful,
** - Non-zero if an error occurred during execution.
*/
int	handle_builtin(char **args, t_shell *shell)
{
	int	result;

	result = 0;
	if (ft_strcmp(args[0], "pwd") == 0)
		result = handle_pwd();
	else if (ft_strcmp(args[0], "cd") == 0)
		result = handle_cd(args, shell);
	else if (ft_strcmp(args[0], "exit") == 0)
		result = handle_exit(shell, args);
	else if (ft_strcmp(args[0], "export") == 0)
		result = handle_export(&shell->env, args);
	else if (ft_strcmp(args[0], "env") == 0)
		result = handle_env(shell, args);
	else if(ft_strcmp(args[0], "unset") == 0)
			result = handle_unset(&shell->env, args);
	else if (ft_strcmp(args[0], "echo") == 0)
		result = handle_echo(shell, args);
	shell->exit_status = result;
	return (result);
}

/*
** is_builtin - Checks if a command is a recognized builtin.
** This function compares the given command string against a fixed
** list of supported builtin command names.
*/
int	is_builtin(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}
