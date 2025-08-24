/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:08:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** execute_exit
**
** This function executes the 'exit' builtin command.
** - Call handle_exit() to process the exit logic and get status.
** - Restore redirections with restore_redirection().
** - If status == 0:
**     * Free the args array.
**     * Destroy the entire shell structure.
**     * Exit the program with shell->exit_status.
** - If status != 0:
**     * Update shell->exit_status.
**     * Free the args array.
**     * Clean up per-command resources.
**     * Return the status without exiting the program.
** - Return 0 as a fallback (should not normally reach here).
*/
int	execute_exit(char **args, t_shell *shell)
{
	int	status;

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

/*
** handle_other_builtins
**
** This function handles all builtin commands except 'exit'.
** - Call handle_builtin() with args and shell, store result.
** - Restore I/O redirections with restore_redirection().
** - Free resources allocated for the current command using
**   cleanup_per_command().
** - Return the builtin's exit status.
*/
int	handle_other_builtins(char **args, t_shell *shell)
{
	int	status;

	status = handle_builtin(args, shell);
	restore_redirection(shell);
	cleanup_per_command(shell);
	return (status);
}
