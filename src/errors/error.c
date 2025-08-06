/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:31:51 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/06 17:23:04 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
