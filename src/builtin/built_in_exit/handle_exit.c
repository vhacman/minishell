/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 19:24:25 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
**   Main exit handler.
** - Handles different argument counts for exit command
** - Delegates logic for 0, 1 or multiple arguments
*/
int	handle_exit(t_shell *shell, char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argc == 1)
		return (exit_default(shell, args), 0);
	else if (argc == 2)
		return (handle_exit_argc_two(shell, args));
	else
	{
		exit_too_many_args(shell);
		return (1);
	}
}
