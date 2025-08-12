/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 12:34:49 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int execute_exit(char **args, t_shell *shell)
{
	int status;

	status = handle_exit(shell, args);
	restore_redirection(shell);
	if (status == 0)
	{
		free_args_array(args);
		destroy_shell(shell);
		exit(shell->exit_status);
	}
	else
	{
		shell->exit_status = status;
		free_args_array(args);
		cleanup_per_command(shell);
		return (status);
	}
	return (0);
}

int handle_other_builtins(char **args, t_shell *shell)
{
	int status;

	status = handle_builtin(args, shell);
	restore_redirection(shell);
	cleanup_per_command(shell);
	return (status);
}
