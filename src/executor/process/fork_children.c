/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:35:11 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 15:23:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
