/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:11:11 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:11:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** apply_input_redirection
**
** This function applies input redirection for a command.
** - Duplicate the current STDIN (fd 0) and save it in
**   saved_stdin, so it can be restored later.
**     * If dup() fails, print error, close input_fd, and return -1.
** - Redirect STDIN to input_fd using dup2().
**     * If dup2() fails, print error, close input_fd and the saved
**       stdin, then return -1.
** - Close the input_fd since it's no longer needed.
** - Store saved_stdin in shell->saved_stdin.
** - Return 0 on success.
*/
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


/*
** handle_single_input_redirect
**
** This function handles a single input redirection token.
** - Validate the redirection syntax with validate_redirect_syntax().
**     * If invalid, close any existing input_fd and return -1.
** - Open the input file (or heredoc) using open_input_file().
**     * If opening fails, close existing input_fd and return -1.
** - Update the current input_fd with update_input_fd(), replacing
**   any previously open file descriptor.
** - Return 0 on success.
*/
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
