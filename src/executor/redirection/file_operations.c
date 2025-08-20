/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:55:07 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:16:09 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	open_regular_file(char *filename, int token_type)
{
	int	fd;
	int	flags;

	if (token_type == TK_IN)
		fd = open(filename, O_RDONLY);
	else if (token_type == TK_OUT)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(filename, flags, 0644);
	}
	else if (token_type == TK_APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		fd = open(filename, flags, 0644);
	}
	else
		return (-1);
	if (fd == -1)
		perror("minishell");
	return (fd);
}

int	open_file_by_type(char *filename, int token_type, t_shell *shell)
{
	if (token_type == TK_HEREDOC)
		return (create_heredoc_pipe(filename, shell));
	return (open_regular_file(filename, token_type));
}

void	restore_redirection(t_shell *shell)
{
	if ((shell->redirect_type == TK_OUT
			|| shell->redirect_type == TK_APPEND)
		&& shell->saved_stdout >= 0)
	{
		dup2(shell->saved_stdout, 1);
		close(shell->saved_stdout);
		shell->saved_stdout = -1;
	}
	restore_input_redirection(shell);
	shell->redirect_type = 0;
}
