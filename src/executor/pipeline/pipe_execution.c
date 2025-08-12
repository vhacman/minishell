/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:50 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:47:03 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Executes a sequence of commands in a pipeline.
**
** Steps:
** 1. Initialize `prev_fd` to -1 (no previous pipe initially).
** 2. Iterate over the linked list of commands (`cmds`):
**    - Call `execute_single_command` to handle execution and
**      pipe creation.
**    - If an error occurs, stop iteration and mark failure.
**    - Update `prev_fd` to the read end of the current pipe
**      if there is a next command; otherwise set to -1.
** 3. If an error occurred and a previous pipe is open,
**    close it to avoid leaks.
** 4. Return 1 if an error occurred, otherwise 0.
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
		if (curr->next)
			prev_fd = pipe_fd[0];
		else
			prev_fd = -1;
		curr = curr->next;
	}
	if (error_occurred && prev_fd != -1)
		close(prev_fd);
	return (error_occurred);
}

/*
** Waits for all child processes to finish and updates the shell's
** exit status.
**
** Steps:
** 1. Loop while `wait` returns a valid PID (> 0).
** 2. If the child exited normally, set `exit_status` to the
**    child's exit code.
** 3. If the child was terminated by a signal, set `exit_status`
**    to 128 + signal number.
** 4. Return the final exit status stored in the shell.
*/
static int	wait_for_children(t_shell *shell)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
	}
	return (shell->exit_status);
}

/*
** Executes a sequence of commands connected by pipes.
**
** Steps:
** 1. Set signal handlers for command execution mode.
** 2. Run the command loop with `execute_commands_loop`.
**    - If an error occurs, restore interactive signals
**      and return 1.
** 3. Wait for all child processes to finish.
** 4. Restore interactive signal handlers.
** 5. Return the shell's final exit status.
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
