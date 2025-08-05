/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:03:40 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 17:55:48 by vhacman          ###   ########.fr       */
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

/*
** Returns 1 if the string is not a valid numeric value or overflows a long.
** Accepts optional leading '+' or '-' sign.
*/
int	check_numeric_overflow(char *str)
{
	int			i;
	int			sign;
	unsigned long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > LONG_MAX)
			return (1);
		if (sign == -1 && result > (unsigned long)LONG_MAX + 1)
			return (1);
		i++;
	}
	return (0);
}
