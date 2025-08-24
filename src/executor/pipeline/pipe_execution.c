/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:50 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:04:33 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** setup_next_pipe
**
** This helper function determines the read end of the next pipe
** for a command in a pipeline.
** - If the current command has a next command:
**     * Check if it already has an output redirection.
**     * If it does, return -1 (pipe is not needed).
**     * Otherwise, return pipe_fd[0] (the read end of the pipe).
** - If there is no next command, return -1.
*/
static int	setup_next_pipe(t_cmd *curr, int pipe_fd[2])
{
	if (curr->next)
	{
		if (has_output_redirection(curr->tokens))
			return (-1);
		else
			return (pipe_fd[0]);
	}
	return (-1);
}

/*
** execute_commands_loop
**
** This function executes a list of commands connected by pipes.
** - Initialize prev_fd to -1 (no previous pipe).
** - Iterate through the command list while no error occurs:
**     * Call execute_single_command() with the current command,
**       the previous pipe read end, the new pipe, and the shell.
**     * If it returns non-zero, mark error_occurred = 1 and stop.
**     * Otherwise, update prev_fd with setup_next_pipe() to keep
**       the pipe's read end for the next command.
**     * Move to the next command in the list.
** - After the loop, if an error occurred and prev_fd is still
**   open, close it to prevent leaks.
** - Return 1 if an error occurred, or 0 otherwise.
*/
static int	execute_commands_loop(t_cmd *cmds, t_shell *shell)
{
	int		pipe_fd[2];
	int		prev_fd;
	t_cmd	*curr;
	int		error_occurred;

	prev_fd = -1;
	curr = cmds;
	error_occurred = 0;
	while (curr && !error_occurred)
	{
		if (execute_single_command(curr, prev_fd, pipe_fd, shell) != 0)
		{
			error_occurred = 1;
			break ;
		}
		prev_fd = setup_next_pipe(curr, pipe_fd);
		curr = curr->next;
	}
	if (error_occurred && prev_fd != -1)
		close(prev_fd);
	return (error_occurred);
}

/*
** wait_for_children
**
** This function waits for all child processes to finish.
** - Call wait() to get the first child process status.
** - While a child process is reaped successfully (pid > 0):
**     * Update shell->exit_status using
**       handle_signal_exit_status() to correctly process the
**       exit code or signal that terminated the child.
**     * Call wait() again to check for other children.
** - When no more children remain, return the last exit_status.
*/
static int	wait_for_children(t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		shell->exit_status = handle_signal_exit_status(status, shell);
		pid = wait(&status);
	}
	return (shell->exit_status);
}

/*
** execute_pipeline
**
** This function executes a pipeline of commands.
** - First, configure signals for command execution with
**   setup_signals_executing().
** - Call execute_commands_loop() to run the linked list of
**   commands connected by pipes.
** - If an error occurs:
**     * Restore interactive signal handling.
**     * Return 1 to indicate failure.
** - Otherwise, wait for all child processes to finish using
**   wait_for_children(), which updates exit_status.
** - Restore interactive signal handling.
** - Return the final exit_status of the shell.
*/
int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int	error_occurred;

	setup_signals_executing();
	error_occurred = execute_commands_loop(cmds, shell);
	if (error_occurred)
	{
		setup_signals_interactive();
		return (1);
	}
	wait_for_children(shell);
	setup_signals_interactive();
	return (shell->exit_status);
}
