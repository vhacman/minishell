/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:31:51 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/22 13:52:07 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Outputs error message, cleans up if needed, and exits with failure.
**
**	How it works
**				If use_errno is true, prints "minishell: " and perror(msg);
**				otherwise prints msg to stderr. If flag is non-zero and
**				context is provided, calls cleanup on the shell context.
**				Finally calls exit(EXIT_FAILURE).
**	Params:
**			msg			- error message string
**			context		- pointer to shell context for cleanup
**			flag		- if non-zero, perform cleanup before exit
**			use_errno	- if non-zero, use perror to include errno info
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
		cleanup((t_shell *)context);
	exit(EXIT_FAILURE);
}

int	print_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
	return (-1);
}

int	print_pipe_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	return (1);
}

/*
Stampa un messaggio di errore su stderr e termina il programma con un codice di
uscita specifico. stampa un msg e un a capo. infine chama exitcode per terminare il programma.
*/
void	ft_error_exit(char *prefix, char *msg, int exit_code)
{
	if (prefix)
	{
		ft_putstr_fd(prefix, 2);
		if (msg)
			ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}
