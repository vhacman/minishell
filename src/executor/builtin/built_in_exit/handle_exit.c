/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:12:08 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static void	handle_exit_with_code(t_shell *shell, char **args, char *exit_code)
{
	if (!is_numeric(exit_code) || check_atol_conversion(exit_code))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putendl_fd(exit_code, STDERR_FILENO);
		ft_putendl_fd("numeric argument required", STDERR_FILENO);
		shell->exit_status = 255;
		free_args_array(args);
		destroy_shell(shell);
		exit(2);
	}
	else
		shell->exit_status = ft_atoi(exit_code);
}

int	handle_exit(t_shell *shell, char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	if (argc == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		shell->exit_status = 0;
		return (0);
	}
	else if (argc == 2)
	{
		handle_exit_with_code(shell, args, args[1]);
		return (0);
	}
	else
	{
		ft_putendl_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
}
