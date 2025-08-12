/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:55:06 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:45:12 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Configures I/O redirection and signal handling for a child process.
**
** Steps:
** 1. If `prev_fd` is valid (not -1):
**    - Redirect its content to STDIN using `dup2`.
**    - Close `prev_fd` to avoid descriptor leaks.
** 2. If the current command has a successor:
**    - Close the read end of `pipe_fd`.
**    - Redirect the write end to STDOUT using `dup2`.
**    - Close the write end after duplication.
** 3. Set up child-specific signal handling via
**    `setup_signals_child`.
*/
static void	setup_child_io_and_signals(t_cmd *curr, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (curr->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	setup_signals_child();
}

/*
** Executes a builtin command in a child process.
**
** Steps:
** 1. Call `handle_builtin` with the current command's
**    arguments and shell context, storing its return
**    value in `status`.
** 2. Clean up all shell resources with `destroy_shell`
**    to prevent memory leaks.
** 3. Terminate the child process using `exit`, passing
**    the builtin's exit status.
*/
static void	execute_builtin_child(t_cmd *curr, t_shell *shell)
{
	int	status;

	status = handle_builtin(curr->args, shell);
	destroy_shell(shell);
	exit(status);
}

/*
** Executes a system command in a child process.
**
** Steps:
** 1. If `curr->path` is NULL:
**    - Print "command not found" with the attempted
**      command name (or empty if unavailable).
**    - Free all shell resources and exit with code 127.
** 2. Build an environment array `envp` from the shell's
**    linked list using `build_envp_from_list`.
**    - If allocation fails, clean up and exit with error.
** 3. Call `execve` with the command path, arguments, and
**    environment array.
**    - If it fails, free `envp`, destroy the shell, and
**      exit with error.
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
		destroy_shell(shell);
		exit(127);
	}
	envp = build_envp_from_list(shell->env);
	if (!envp)
	{
		destroy_shell(shell);
		exit_with_error("malloc", NULL, 0, 1);
	}
	if (execve(curr->path, curr->args, envp) == -1)
	{
		free_args_array(envp);
		destroy_shell(shell);
		exit_with_error("execve", NULL, 0, 1);
	}
}

/*
** Executes a single child process in a pipeline.
**
** Steps:
** 1. Configure file descriptors and signals for the child
**    process using `setup_child_io_and_signals`.
**    - Redirects input/output based on `prev_fd` and `pipe_fd`.
** 2. If the command is a builtin (`curr->is_builtin`):
**    - Execute it directly via `execute_builtin_child`.
** 3. Otherwise:
**    - Run it as an external command via
**      `execute_system_command`.
*/
void	execute_child_process(t_cmd *curr, int prev_fd,
								int *pipe_fd, t_shell *shell)
{
	setup_child_io_and_signals(curr, prev_fd, pipe_fd);
	if (curr->is_builtin)
		execute_builtin_child(curr, shell);
	else
		execute_system_command(curr, shell);
}
