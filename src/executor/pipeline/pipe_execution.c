/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:50 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:03:48 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
