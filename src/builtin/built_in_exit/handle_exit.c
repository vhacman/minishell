/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 17:52:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	handle_exit(t_shell *shell, char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (argc == 1)
	{
		exit_default(shell, args);
		return (0);
	}
	else if (argc == 2)
	{
		if (!is_numeric(args[1]))
		{
			exit_non_numeric(shell, args[1]);
			return (2);
		}
		else if (check_numeric_overflow(args[1]))
		{
			exit_non_numeric(shell, args[1]);
			return (2);
		}
		else
		{
			exit_with_code(shell, args, args[1]);
			return (0);
		}
	}
	else
	{
		exit_too_many_args(shell);
		return (1);
	}
}