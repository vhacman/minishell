/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 13:33:28 by vhacman          ###   ########.fr       */
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
		shell->exit_status = 0;
		return (0);
	}
	else if (argc == 2)
	{
		if (!is_numeric(args[1]) || check_numeric_overflow(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			shell->exit_status = 255;
			free_args_array(args);
			destroy_shell(shell);
			exit (2);
		}
		else
		{
			shell->exit_status = ft_atoi(args[1]);
			return (0);
		}
	}
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
}
