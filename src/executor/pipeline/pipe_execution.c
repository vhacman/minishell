/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:50 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:09:46 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

static int	wait_for_children(t_shell *shell)
{
	int		status;
	pid_t	pid;
	int		last_exit_status;

	last_exit_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		last_exit_status = handle_signal_exit_status(status, shell);
		pid = wait(&status);
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
