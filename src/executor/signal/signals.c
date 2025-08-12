#include "../../include/minishell.h"

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
