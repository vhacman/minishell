/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:24 by begiovan          #+#    #+#             */
/*   Updated: 2025/07/15 10:25:23 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** g_signal - Global signal indicator for async-safe communication.
**
** This volatile sig_atomic_t variable stores the last signal received.
** It is updated in signal handlers to avoid unsafe operations and
** is later processed in the main execution flow
** (e.g., in check_signal_received).
** It ensures proper, reentrant-safe signal acknowledgment.
*/
volatile sig_atomic_t	g_signal = 0;

/*
** signal_handler_interactive - Handles signals while reading prompt input.
** @sig: The received signal number.
** - On SIGINT (Ctrl+C):
**     - Sets g_signal to SIGINT for async detection.
**     - Prints newline to flush current line.
**     - Resets readline buffer via rl_replace_line().
**     - Refreshes prompt with rl_redisplay().
**
** - On SIGQUIT: ignored, does not update g_signal or terminal state.
**
** This handler ensures user input is gracefully interrupted without
** breaking the readline interface or leaving garbage in the terminal.
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
** signal_handler_executing - Handles signals during command execution.
**
** @sig: The received signal number.
**
** - On SIGINT (Ctrl+C):
**     - Sets g_signal to SIGINT.
**     - Prints newline to reflect interruption.
**
** - On SIGQUIT (Ctrl+\):
**     - Sets g_signal to SIGQUIT.
**     - Prints "Quit: 3" to indicate forced termination.
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
** setup_signal_action - Sets a handler for a specific signal.
**

** @flags:   Flags passed to sigaction (e.g., SA_RESTART).
**
** This utility function encapsulates sigaction setup with:
** - Empty signal mask (no blocked signals during handler).
** - Specified handler and flags.
**
** Used by all setup_signals_* functions to manage signal behavior
** across interactive, executing, and child states.
*/
void	setup_signal_action(int signal, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigaction(signal, &sa, NULL);
}
