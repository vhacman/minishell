#include "../../include/minishell.h"

void	setup_signals_interactive(void)
{
	setup_signal_action(SIGINT, signal_handler_interactive, SA_RESTART);
	setup_signal_action(SIGQUIT, SIG_IGN, 0);
}

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
