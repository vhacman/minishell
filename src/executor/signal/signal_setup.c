/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:18:47 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/12 16:48:27 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Configures signal handling for interactive shell mode.
**
** Steps:
** 1. Set a custom handler for SIGINT using
**    `signal_handler_interactive`, with the SA_RESTART flag
**    to automatically restart interrupted system calls.
** 2. Ignore SIGQUIT by setting its action to SIG_IGN.
** This setup ensures predictable behavior while the user
** interacts with the prompt.
*/
void	setup_signals_interactive(void)
{
	setup_signal_action(SIGINT, signal_handler_interactive, SA_RESTART);
	setup_signal_action(SIGQUIT, SIG_IGN, 0);
}

/*
** Sets signal handling during command pipeline execution.
**
** Details:
** - SIGINT: ignored (`SIG_IGN`) to prevent interrupting the
**   main parent process.
** - SIGQUIT: ignored to avoid termination with a core dump.
** - SA_RESTART: ensures interrupted system calls are
**   automatically restarted.
*/
void	setup_signals_executing(void)
{
	setup_signal_action(SIGINT, SIG_IGN, SA_RESTART);
	setup_signal_action(SIGQUIT, SIG_IGN, SA_RESTART);
}

/*
** Restores default signal handling in a child process.
**
** Details:
** - SIGINT: set to default behavior (`SIG_DFL`) so the child
**   process can be interrupted by Ctrl+C.
** - SIGQUIT: set to default behavior so the child can be
**   terminated and produce a core dump if triggered.
*/
void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
** Handles and translates a child process exit status into a shell exit code.
**
** Parameters:
** - status: The raw status returned by `wait()` or `waitpid()`.
** - shell: Pointer to the shell structure to update `exit_status`.
**
** Process:
** 1. If the process was terminated by a signal (`WIFSIGNALED`):
**    - SIGINT → exit status 130 (terminated by Ctrl+C).
**    - SIGQUIT → exit status 131 (terminated by Ctrl+\).
**    - Any other signal → 128 + signal number.
** 2. If the process exited normally (`WIFEXITED`):
**    - Use the process exit code directly.
** 3. If neither condition matches:
**    - Set and return exit status 1 (generic error).
**
** Returns:
** - The computed shell exit status.
*/
int	handle_signal_exit_status(int status, t_shell *shell)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			shell->exit_status = 130;
		else if (sig == SIGQUIT)
			shell->exit_status = 131;
		else
			shell->exit_status = 128 + sig;
		return (shell->exit_status);
	}
	else if (WIFEXITED(status))
	{
		shell->exit_status = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	shell->exit_status = 1;
	return (1);
}

/*
** Checks if a signal was received and updates the shell's
** exit status accordingly.
**
** Steps:
** 1. If `g_signal` is SIGINT:
**    - Set `exit_status` to 130 (Ctrl+C convention).
**    - Reset `g_signal` to 0.
**    - Return 130.
** 2. If `g_signal` is SIGQUIT:
**    - Set `exit_status` to 131 (Ctrl+\ convention).
**    - Reset `g_signal` to 0.
**    - Return 131.
** 3. If no relevant signal is pending, reset `g_signal`
**    to 0 and return 0.
*/
int	check_signal_received(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
		return (130);
	}
	else if (g_signal == SIGQUIT)
	{
		shell->exit_status = 131;
		g_signal = 0;
		return (131);
	}
	g_signal = 0;
	return (0);
}
