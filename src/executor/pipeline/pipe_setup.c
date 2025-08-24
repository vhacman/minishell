/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:35:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:08:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** setup_command_execution
**
** This function prepares a command for execution by creating
** pipes (if needed) and forking a child process.
** - If the current command has a next command:
**     * Create a new pipe with pipe().
**     * If pipe() fails, print an error and return 1.
** - Fork a new process with fork() and store the PID in *pid.
**     * If fork() fails, print an error and return 1.
** - Return 0 on success.
*/
int	setup_command_execution(t_cmd *curr, int prev_fd, int *pipe_fd, pid_t *pid)
{
	(void)prev_fd;
	if (curr->next && pipe(pipe_fd) == -1)
		return (print_error("pipe"));
	*pid = fork();
	if (*pid == -1)
		return (print_error("fork"));
	return (0);
}

/*
** execute_single_command
**
** This function executes one command in a pipeline.
** - Call setup_command_execution() to create pipes and fork.
**     * If setup fails, return 1.
** - In the child process (pid == 0):
**     * Call execute_child_process() to handle redirections,
**       signals, and execute the command.
** - In the parent process:
**     * If prev_fd is valid, close it (no longer needed).
**     * If there is a next command:
**         - Close the write end of the pipe.
**         - If the command already has an output redirection,
**           also close the read end to avoid unused descriptors.
** - Return 0 on success.
*/
int	execute_single_command(t_cmd *curr, int prev_fd, int *pipe_fd,
		t_shell *shell)
{
	pid_t	pid;

	if (setup_command_execution(curr, prev_fd, pipe_fd, &pid) == 1)
		return (1);
	if (pid == 0)
		execute_child_process(curr, prev_fd, pipe_fd, shell);
	if (prev_fd != -1)
		close(prev_fd);
	if (curr->next)
	{
		close(pipe_fd[1]);
		if (has_output_redirection(curr->tokens))
			close(pipe_fd[0]);
	}
	return (0);
}
