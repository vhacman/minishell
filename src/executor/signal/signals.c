/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:18:47 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/12 16:50:56 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Global variable to store the last received signal number.
**
** Type:
** - `volatile sig_atomic_t`: Ensures atomic read/write operations
**   and prevents compiler optimizations that could break signal safety.
**
** Purpose:
** - Used to safely communicate between a signal handler and the main program.
** - Updated inside signal handlers to indicate which signal was caught.
*/
volatile sig_atomic_t	g_signal = 0;

/*
** Handles signals in interactive mode (e.g., while waiting for user input).
**
** Parameters:
** - sig: The signal number received by the process.
**
** Behavior for SIGINT (Ctrl+C):
** 1. Sets the global variable `g_signal` to `SIGINT` to record the event.
** 2. Prints a newline to move the cursor to the next line.
** 3. Resets the readline buffer using `rl_on_new_line` and `rl_replace_line`.
** 4. Refreshes the prompt display with `rl_redisplay`.
**
** - This handler is used during the interactive prompt to avoid
**   terminating the shell on Ctrl+C.
*/
void	signal_handler_interactive(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
** Handles signals during command execution (non-interactive mode).
** Behavior:
** - SIGINT (Ctrl+C):
**   1. Sets `g_signal` to `SIGINT`.
**   2. Prints a newline to indicate interruption.
** - SIGQUIT (Ctrl+\):
**   1. Sets `g_signal` to `SIGQUIT`.
**   2. Prints "Quit: 3" to indicate the quit signal.
** - This handler is active while a command is executing, ensuring the shell
**   displays appropriate messages instead of exiting immediately.
*/
void	signal_handler_executing(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ft_printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
		ft_printf("Quit: 3\n");
	}
}

/*
** Sets a custom action for a specific signal.
**
** Steps:
** 1. Initialize an empty signal mask to block no signals
**    during the handler execution.
** 2. Assign the provided `handler` function to `sa_handler`.
** 3. Set any additional behavior flags (e.g., SA_RESTART).
** 4. Apply the new action for the specified `signal` using
**    `sigaction`.
*/
void	setup_signal_action(int signal, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigaction(signal, &sa, NULL);
}
