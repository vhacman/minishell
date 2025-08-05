/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:01 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/05 18:02:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_child_process_from_args(char *cmd_path, char **args, t_shell *shell)
{
	t_cmd	temp;

	temp.path = cmd_path;
	temp.args = args;
	temp.next = NULL;
	temp.is_builtin = 0;

	execute_child_process(&temp, -1, NULL, shell);
}

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
	cleanup(shell, 1);
}

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
	{
		execute_child_process_from_args(cmd_path, args, shell);
		// setup_child_process(cmd_path, args, shell);
	}
	else
		handle_parent_process(pid, shell);
	return (shell->exit_status);
}
