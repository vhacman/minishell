/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:37:44 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:00:03 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** is_n_flag
**
** This helper function checks if a string represents the '-n'
** flag used by the echo command.
** - Return 0 if the string is NULL, does not start with '-',
**   or the second character is not 'n'.
** - Starting from index 2, verify that all remaining characters
**   are also 'n'.
** - If any other character is found, return 0.
** - If the string matches "-n", "-nn", "-nnn", etc.,
**   return 1 (true).
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
** handle_echo
**
** This function implements the behavior of the 'echo' builtin.
** - Ignore the shell parameter since it is not used here.
** - Initialize print_newline to 1 (true).
** - Skip over any "-n" flags at the start of args:
**     * If found, set print_newline to 0 (suppress newline).
** - Print each argument separated by a space:
**     * Only print non-empty strings.
**     * Add a space if another argument follows.
** - After printing all arguments:
**     * If print_newline is still 1, add a final newline.
** - Always return 0 (success).
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
