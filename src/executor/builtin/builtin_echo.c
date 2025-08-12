/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:37:44 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:35:29 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Checks if a given string is a valid '-n' flag for the echo command.
** 1. Immediately return 0 if:
**    - `str` is NULL.
**    - First character is not '-'.
**    - Second character is not 'n'.
** 2. Start from index 2, verify that all remaining characters are 'n'.
**    - If any character is different from 'n', return 0.
** 3. If all checks pass, return 1.
**
** Notes:
** - Accepts multiple 'n' characters (e.g., "-n", "-nnn").
** - Used to detect when `echo` should suppress the trailing newline.
*/
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

/*
** Implements the `echo` built-in command.
** Process:
** 1. Initialize `print_newline` to 1 (default: print newline).
** 2. Parse consecutive '-n' flags at the start of the arguments:
**    - If found, set `print_newline` to 0 and skip these arguments.
** 3. Print remaining arguments separated by a single space.
**    - Do not print a trailing space after the last argument.
** 4. If `print_newline` is still 1, print a newline at the end.
*/
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
