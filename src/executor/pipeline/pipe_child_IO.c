/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child_IO.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:46:25 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:01:20 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** setup_child_pipes
**
** This helper function configures input/output pipes for a child
** process during pipeline execution.
** - If prev_fd is valid (not -1):
**     * Check if the command already has an input redirection.
**     * If not, duplicate prev_fd to STDIN.
**     * Close prev_fd after use.
** - If the command has a next command and a pipe_fd is provided:
**     * Check if the command already has an output redirection.
**     * Close the read end of the pipe (pipe_fd[0]).
**     * If no output redirection exists, duplicate pipe_fd[1]
**       to STDOUT.
**     * Close the write end of the pipe (pipe_fd[1]).
*/
static void	setup_child_pipes(t_cmd *curr, int prev_fd, int *pipe_fd)
{
	int	has_input_redir;
	int	has_output_redir;

	if (prev_fd != -1)
	{
		has_input_redir = has_input_redirection(curr->tokens);
		if (!has_input_redir)
		{
			if (dup2(prev_fd, STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(1);
			}
		}
		close(prev_fd);
	}
	if (curr->next && pipe_fd)
	{
		has_output_redir = has_output_redirection(curr->tokens);
		close(pipe_fd[0]);
		if (!has_output_redir)
		{
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(1);
			}
		}
		close(pipe_fd[1]);
	}
}

/*
** setup_child_redir_and_signals
**
** This helper function prepares a child process before
** executing a command.
** - If the command has tokens, call
**   handle_redirection_with_tokens() to set up I/O redirections.
**     * If redirection fails, destroy the shell structure and
**       exit with status 1.
** - After handling redirections, configure signal handlers
**   appropriate for a child process using setup_signals_child().
*/
static void	setup_child_redir_and_signals(t_cmd *curr, t_shell *shell)
{
	if (curr->tokens)
	{
		if (handle_redirection_with_tokens(curr->tokens, shell) == -1)
		{
			destroy_shell(shell);
			exit(1);
		}
	}
	setup_signals_child();
}

/*
 * setup_child_io_and_signals:
 * Entry point combining pipes setup and
 * redirections/signals configuration.
 */
void	setup_child_io_and_signals(t_cmd *curr,
					int prev_fd, int *pipe_fd, t_shell *shell)
{
	setup_sigpipe_handling();
	setup_child_pipes(curr, prev_fd, pipe_fd);
	setup_child_redir_and_signals(curr, shell);
}
