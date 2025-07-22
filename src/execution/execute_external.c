/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:01 by begiovan          #+#    #+#             */
/*   Updated: 2025/07/15 10:35:04 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** setup_child_process - Prepares and executes the child process.
** This function is called in the child process after fork().
** It sets up signal behavior specific to child execution and
** attempts to execute the binary using execve().
** - Replaces current process with the executable.
** - If execve() fails, exits the process via exit_with_error().
**
** Uses the global `environ` as the environment for execve().
*/
static void	setup_child_process(char *command_path, char **args)
{
	extern char	**environ;

	setup_signals_child();
	if (execve(command_path, args, environ) == -1)
		exit_with_error("execve", NULL, 0, 1);
}

/*
** print_signal_message - Displays appropriate message for signal termination.
** @signal_number: The signal number that caused termination.
** @status: The status returned by waitpid().
** - Prints human-readable message based on signal type.
** - Includes core dump information when available.
*/
static void	print_signal_message(int signal_number, int status)
{
	if (signal_number == SIGQUIT)
	{
		if (WCOREDUMP(status))
			ft_printf("Quit (core dumped)\n");
		else
			ft_printf("Quit\n");
	}
	else if (signal_number == SIGTERM)
	{
		if (WCOREDUMP(status))
			ft_printf("Terminated (core dumped)\n");
		else
			ft_printf("Terminated\n");
	}
	else if (signal_number == SIGKILL)
		ft_printf("Killed\n");
	else if (signal_number == SIGSEGV)
	{
		if (WCOREDUMP(status))
			ft_printf("Segmentation fault (core dumped)\n");
		else
			ft_printf("Segmentation fault\n");
	}
}

/*
** handle_parent_process - Handles the parent process after fork().
** @pid: Process ID of the child process.
** @shell: Pointer to the shell structure.
** - Waits for the child process to complete using waitpid().
** - Handles different exit conditions:
**   - Signal interruption (SIGINT)
**   - Signal termination (prints message and sets exit status)
**   - Normal exit (sets exit status)
** - Restores interactive signal handling after execution.
*/
static void	handle_parent_process(pid_t pid, t_shell *shell)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		if (g_signal == SIGINT)
			shell->exit_status = 130;
		else
		{
			perror("waitpid");
			shell->exit_status = 1;
		}
	}
	else
	{
		if (WIFSIGNALED(status))
			print_signal_message(WTERMSIG(status), status);
		handle_signal_exit_status(status, shell);
	}
	setup_signals_interactive();
}

/*
** execute_external_command - Launches a non-builtin command.
** This function runs an external command via fork() and execve().
** - Sets execution-mode signals.
** - Forks the current process.
**   - In child: calls setup_child_process().
**   - In parent: waits and handles child exit with handle_parent_process().
** - On fork failure, restores signals and exits via exit_with_error().
**
** Return:
** - The exit status assigned to shell->exit_status.
*/
int	execute_external_command(char *cmd_path, char **args, t_shell *shell)
{
	pid_t	pid;

	setup_signals_executing();
	pid = fork();
	if (pid == -1)
	{
		setup_signals_interactive();
		exit_with_error("fork", shell, 1, 1);
	}
	else if (pid == 0)
		setup_child_process(cmd_path, args);
	else
		handle_parent_process(pid, shell);
	return (shell->exit_status);
}
