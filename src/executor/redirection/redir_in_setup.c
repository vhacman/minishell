/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:11:11 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:11:38 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	apply_input_redirection(int input_fd, t_shell *shell)
{
	int	saved_stdin;

	saved_stdin = dup(0);
	if (saved_stdin == -1)
	{
		perror("minishell: dup");
		close(input_fd);
		return (-1);
	}
	if (dup2(input_fd, 0) == -1)
	{
		perror("minishell: dup2");
		close(input_fd);
		close(saved_stdin);
		return (-1);
	}
	close(input_fd);
	shell->saved_stdin = saved_stdin;
	return (0);
}

int	handle_single_input_redirect(t_token *curr, t_shell *shell, int *input_fd)
{
	int	new_input_fd;

	if (validate_redirect_syntax(curr) == -1)
	{
		if (*input_fd != -1)
			close(*input_fd);
		return (-1);
	}
	new_input_fd = open_input_file(curr, shell);
	if (new_input_fd == -1)
	{
		if (*input_fd != -1)
			close(*input_fd);
		return (-1);
	}
	update_input_fd(input_fd, new_input_fd);
	return (0);
}
