/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:18:47 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/12 16:49:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Prints a descriptive message based on the received signal and process status.
**
** Parameters:
** - signal_number: The signal that caused the process termination.
** - status: The raw status returned by `wait()` or `waitpid()`, used to check
**   if a core dump occurred (`WCOREDUMP`).
**
** Process:
** 1. For SIGQUIT:
**    - Print "Quit" or "Quit (core dumped)" if applicable.
** 2. For SIGTERM:
**    - Print "Terminated" or "Terminated (core dumped)" if applicable.
** 3. For SIGKILL:
**    - Print "Killed".
** 4. For SIGSEGV:
**    - Print "Segmentation fault" or "Segmentation fault (core dumped)".
**
** Notes:
** - Core dump messages are printed only if `WCOREDUMP(status)` is true.
** - No action is taken for signals not explicitly handled here.
*/
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
