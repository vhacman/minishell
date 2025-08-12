/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:48:12 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 11:50:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
