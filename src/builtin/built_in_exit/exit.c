/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:03:40 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/15 17:12:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** exit_non_numeric - Handles `exit` with a non-numeric argument.
** - Prints error message: "minishell: exit: <arg>: numeric argument required".
** - Frees the argument vector and shell memory.
** - Exits the shell immediately with exit code 255.
*/
void	exit_non_numeric(t_shell *shell, char *arg, char **args)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_split(args);
	cleanup(shell);
	exit(2);
}

/*
** exit_with_code - Handles `exit <numeric_code>` case.
** - Converts arg to long using ft_atol().
** - Frees argument vector and shell memory.
** - Exits the shell using the numeric code (cast to unsigned char).
** Ensures the exit code is constrained to 0–255.
*/
void	exit_with_code(t_shell *shell, char *arg, char **args)
{
	long	code;

	code = ft_atol(arg);
	free_split(args);
	cleanup(shell);
	exit((unsigned char)code);
}

/*
** exit_default - Handles `exit` with no arguments.
** - Frees arguments and shell memory.
** - Exits using the shell's last stored exit_status.
*/
void	exit_default(t_shell *shell, char **args)
{
	free_split(args);
	cleanup(shell);
	exit(shell->exit_status);
}

/*
** exit_too_many_args - Handles `exit` with more than one argument.
** - Prints error: "minishell: exit: too many arguments".
** - Does not terminate the shell.
** - Sets shell->exit_status to 1 to reflect failure.
*/
int	exit_too_many_args(t_shell *shell)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	shell->exit_status = 1;
	return (1);
}
