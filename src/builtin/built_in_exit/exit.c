/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:03:40 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 19:24:38 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	exit_non_numeric(t_shell *shell, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	shell->exit_status = 2;
	return (2);
}

void	exit_with_code(t_shell *shell, char **args, char *code_str)
{
	long	code;

	code = ft_atol(code_str) % 256;
	free_args_array(args);
	cleanup_and_exit(shell, args, code);
}

void	exit_default(t_shell *shell, char **args)
{
	free_args_array(args);
	cleanup_and_exit(shell, args, shell->exit_status);
}

int	exit_too_many_args(t_shell *shell)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	shell->exit_status = 1;
	return (1);
}

int	handle_exit_argc_two(t_shell *shell, char **args)
{
	if (!is_numeric(args[1]) || check_numeric_overflow(args[1]))
	{
		exit_non_numeric(shell, args[1]);
		return (2);
	}
	exit_with_code(shell, args, args[1]);
	return (0);
}
