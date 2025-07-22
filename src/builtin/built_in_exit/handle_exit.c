/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 16:25:09 by vhacman          ###   ########.fr       */
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
		exit_default(shell, args);
	else if (argc == 2)
	{
		if (!is_numeric(args[1]))
			exit_non_numeric(shell, args[1], args);
		else
			exit_with_code(shell, args[1], args);
	}
	else
		return (exit_too_many_args(shell));
	return (0);
}
