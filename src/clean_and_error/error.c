/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:31:51 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:11:35 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Prints an error message, optionally cleans up resources,
** and terminates the program.
**
** 1. If `use_errno` is non-zero:
**    - Print "minishell: " to stderr.
**    - Call `perror` with `msg` to display the system
**      error message.
** 2. If `use_errno` is zero:
**    - Print `msg` directly to stderr.
** 3. If `flag` is non-zero and `context` is provided:
**    - Cast `context` to `t_shell *` and call
**      `cleanup_per_command` to free per-command resources.
** 4. Exit the program with `EXIT_FAILURE`.
*/
void	exit_with_error(char *msg, void *context, int flag, int use_errno)
{
	if (use_errno)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(msg);
	}
	else
		ft_putstr_fd(msg, 2);
	if (flag && context)
		cleanup_per_command((t_shell *)context);
	exit(EXIT_FAILURE);
}

/*
** Prints a formatted error message to stderr and returns -1.
**
** 1. Print "minishell: " to stderr.
** 2. Use `perror` with `msg` to append the system error
**    description.
** 3. Return -1, allowing the caller to detect the error
**    while preserving standard error reporting.
*/
int	print_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
	return (-1);
}

/*
** Prints a syntax error message for an unexpected pipe token.
**
** 1. Output a fixed error message to stderr indicating a
**    syntax error with the '|' token.
** 2. Return 1 to signal an error condition to the caller.
*/
int	print_pipe_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	return (1);
}
