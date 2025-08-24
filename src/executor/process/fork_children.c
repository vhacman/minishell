/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:35:11 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:06:29 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** setup_child_pipe
**
** This function connects a child process to one end of a pipe.
** - If is_left is true (1):
**     * Close the read end of the pipe (pipe_fd[0]).
**     * Duplicate the write end (pipe_fd[1]) to STDOUT so the
**       child writes into the pipe.
**     * If dup2 fails, print error, close pipe_fd[1], and
**       return -1.
**     * Close the write end after duplicating.
** - If is_left is false (0):
**     * Close the write end of the pipe (pipe_fd[1]).
**     * Duplicate the read end (pipe_fd[0]) to STDIN so the
**       child reads from the pipe.
**     * If dup2 fails, print error, close pipe_fd[0], and
**       return -1.
**     * Close the read end after duplicating.
** - Return 0 on success.
*/
int	setup_child_pipe(int pipe_fd[2], int is_left)
{
	if (is_left)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(pipe_fd[1]);
			return (-1);
		}
		close(pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(pipe_fd[0]);
			return (-1);
		}
		close(pipe_fd[0]);
	}
	return (0);
}

/*
** fork_first_child
**
** This function forks the first child process in a pipe setup.
** - Call fork() and store the returned PID.
** - If fork fails:
**     * Print error with perror().
**     * Close both ends of the pipe.
**     * Restore interactive signals.
**     * Return -1.
** - In the child process (pid == 0):
**     * Call setup_child_pipe() with direction = 1 to connect
**       STDOUT to the pipe.
**     * If setup fails, exit(1).
**     * Execute the command using execute_cmd_in_pipe().
** - In the parent, return the child's PID.
*/
int	fork_first_child(t_cmd *cmd1, t_shell *shell, int pipe_fd[2])
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		setup_signals_interactive();
		return (-1);
	}
	if (pid1 == 0)
	{
		if (setup_child_pipe(pipe_fd, 1) == -1)
			exit(1);
		execute_cmd_in_pipe(cmd1, shell);
	}
	return (pid1);
}

/*
** fork_second_child
**
** This function forks the second child process in a pipe setup.
** - Call fork() and store the returned PID.
** - If fork fails:
**     * Print error with perror().
**     * Close both ends of the pipe.
**     * Kill the first child process (pid1) with SIGTERM to
**       prevent it from running alone.
**     * Wait for the first child to terminate.
**     * Restore interactive signals.
**     * Return -1.
** - In the child process (pid == 0):
**     * Call setup_child_pipe() with direction = 0 to connect
**       STDIN to the pipe.
**     * If setup fails, exit(1).
**     * Execute the command using execute_cmd_in_pipe().
** - In the parent, return the second child's PID.
*/
int	fork_second_child(t_cmd *cmd2, t_shell *shell, int pipe_fd[2], pid_t pid1)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		kill(pid1, SIGTERM);
		waitpid(pid1, NULL, 0);
		setup_signals_interactive();
		return (-1);
	}
	if (pid2 == 0)
	{
		if (setup_child_pipe(pipe_fd, 0) == -1)
			exit(1);
		execute_cmd_in_pipe(cmd2, shell);
	}
	return (pid2);
}
