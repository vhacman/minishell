/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:55:06 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:02:34 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** execute_builtin_child
**
** This helper function runs a builtin command inside a child
** process.
** - Call handle_builtin() with the command arguments to execute
**   the builtin and store its status.
** - If the command has tokens:
**     * Restore any modified redirections with restore_redirection().
**     * Free the token list.
** - Destroy the shell structure to release all resources.
** - Exit the child process with the builtin's exit status.
*/
static void	execute_builtin_child(t_cmd *curr, t_shell *shell)
{
	int	status;

	status = handle_builtin(curr->args, shell);
	if (curr->tokens)
	{
		restore_redirection(shell);
		free_token_list(&curr->tokens);
	}
	destroy_shell(shell);
	exit(status);
}

/*
** execute_system_command
**
** This helper function executes an external (non-builtin) command
** in the child process.
** - If the command path is missing:
**     * If arguments exist, use args[0] as the command name.
**     * Print "command not found" to stderr.
**     * Exit with status 127.
** - Build the environment array (envp) from the shell's env list.
**     * If building fails, exit with status 1.
** - Call execve() with the command path, arguments, and envp.
**     * If execve() fails, free envp and exit with status 1.
*/
static void	execute_system_command(t_cmd *curr, t_shell *shell)
{
	char		**envp;
	const char	*cmd;

	cmd = "";
	if (!curr->path)
	{
		if (curr->args && curr->args[0])
			cmd = curr->args[0];
		ft_printf("minishell: %s: command not found\n", cmd);
		cleanup_and_exit(curr, shell, 127);
	}
	envp = build_envp_from_list(shell->env);
	if (!envp)
		cleanup_and_exit(curr, shell, 1);
	if (execve(curr->path, curr->args, envp) == -1)
	{
		free_args_array(envp);
		cleanup_and_exit(curr, shell, 1);
	}
}

/*
** execute_child_process
**
** This function executes a command in the child process.
** - First, configure I/O redirections and signals with
**   setup_child_io_and_signals().
** - If the command is a builtin (curr->is_builtin is true):
**     * Call execute_builtin_child() to run it.
** - Otherwise:
**     * Call execute_system_command() to run an external
**       program using execve().
*/
void	execute_child_process(t_cmd *curr, int prev_fd,
								int *pipe_fd, t_shell *shell)
{
	setup_child_io_and_signals(curr, prev_fd, pipe_fd, shell);
	if (curr->is_builtin)
		execute_builtin_child(curr, shell);
	else
		execute_system_command(curr, shell);
}
