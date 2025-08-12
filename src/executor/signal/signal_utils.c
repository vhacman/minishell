#include "../../include/minishell.h"

void	print_signal_message(int signal_number, int status)
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
