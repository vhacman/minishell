/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:55:07 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:10:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** open_regular_file
**
** This function opens a regular file based on the type of
** redirection token.
** - If token_type == TK_IN: open the file in read-only mode.
** - If token_type == TK_OUT: open for writing, create if needed,
**   and truncate existing content.
** - If token_type == TK_APPEND: open for writing, create if
**   needed, and append to the file.
** - If token_type does not match, return -1.
** - On failure, print an error with perror("minishell").
** - Return the file descriptor on success.
*/
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

/*
** open_file_by_type
**
** This function opens a file depending on the redirection type.
** - If the type is TK_HEREDOC, call create_heredoc_pipe().
** - Otherwise, use open_regular_file() for standard redirections
**   (input, output, append).
** - Return the resulting file descriptor or error code.
*/
int	open_file_by_type(char *filename, int token_type, t_shell *shell)
{
	if (token_type == TK_HEREDOC)
		return (create_heredoc_pipe(filename, shell));
	return (open_regular_file(filename, token_type));
}

/*
** restore_redirection
**
** This function restores the original standard input/output after
** a redirection.
** - If the last redirection was output (">" or ">>") and a saved
**   stdout descriptor exists:
**     * Restore stdout using dup2().
**     * Close the saved descriptor.
**     * Reset saved_stdout to -1.
** - Always call restore_input_redirection() to restore stdin if
**   it was modified.
** - Reset redirect_type to 0 (no active redirection).
*/
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
