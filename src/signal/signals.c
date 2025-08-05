/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:24 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/05 17:59:38 by vhacman          ###   ########.fr       */
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

void	setup_signal_action(int signal, void (*handler)(int), int flags)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = flags;
	sigaction(signal, &sa, NULL);
}
