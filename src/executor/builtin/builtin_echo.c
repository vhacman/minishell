/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:37:44 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 11:52:22 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_n_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	handle_echo(t_shell *shell, char **args)
{
	int		i;
	int		print_newline;

	(void)shell;
	print_newline = 1;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		print_newline = 0;
		i++;
	}
	while (args[i])
	{
		if (args[i][0])
			ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
