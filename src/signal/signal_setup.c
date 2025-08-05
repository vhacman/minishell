/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:21 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/05 17:59:53 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** setup_signals_interactive - Configures signals for shell prompt mode.
**
** This function sets up behavior for the shell while it is waiting for
** user input interactively.
**
** Behavior:
** - SIGINT  → handled by signal_handler_interactive (e.g., Ctrl+C clears line).
** - SIGQUIT → ignored completely (e.g., Ctrl+\ has no effect).
**
** Uses setup_signal_action() to apply handlers with the proper flags.
*/
void	setup_signals_interactive(void)
{
	setup_signal_action(SIGINT, signal_handler_interactive, SA_RESTART);
	setup_signal_action(SIGQUIT, SIG_IGN, 0);
}

/*
MODIFICHE:
prima:
void	setup_signals_executing(void)
{
	setup_signal_action(SIGINT, signal_handler_executing, 0);
	setup_signal_action(SIGQUIT, signal_handler_executing, 0);
}
dopo:
void	setup_signals_executing(void)
{
	setup_signal_action(SIGINT, SIG_IGN, SA_RESTART);
	setup_signal_action(SIGQUIT, SIG_IGN, SA_RESTART);
}
	Perché?
In Bash la shell madre ignora entrambi i segnali quando 
c’è un processo in foreground,
così solo il figlio li riceve (e può fare core-dump su SIGQUIT).
Il flag SA_RESTART fa ripartire automaticamente la waitpid()
se venisse interrotta.
*/
void	setup_signals_executing(void)
{
	setup_signal_action(SIGINT, SIG_IGN, SA_RESTART);
	setup_signal_action(SIGQUIT, SIG_IGN, SA_RESTART);
}

void	setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

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
** check_signal_received - Checks and applies pending asynchronous signals.
** Uses a global `g_signal` to detect asynchronous signals like SIGINT or
** SIGQUIT that may have been captured during readline or execution.
** - If SIGINT (Ctrl+C) was received:
**     - Sets exit_status to 130.
** - If SIGQUIT (Ctrl+\) was received:
**     - Sets exit_status to 131.
** - In all cases, resets g_signal to 0 after processing.
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
