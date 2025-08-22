/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:48:12 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 12:22:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
	else if (ft_strcmp(args[0], "unset") == 0)
		result = handle_unset(&shell->env, args);
	else if (ft_strcmp(args[0], "echo") == 0)
		result = handle_echo(shell, args);
	shell->exit_status = result;
	return (result);
}

/*
** Checks whether a given command string corresponds to a
** supported built-in command in the minishell.
**
** Parameters:
** - command: String containing the command to check.
**
** Process:
** 1. Compare the `command` string with each built-in command
**    name using `ft_strcmp`.
** 2. The supported built-ins are: "exit", "cd", "pwd", "env",
**    "echo", "export", and "unset".
** 3. If a match is found, return 1 to indicate it is a built-in.
** 4. If no match is found after all comparisons, return 0.
**
** Return:
** - 1 if `command` is a built-in command.
** - 0 otherwise.
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
