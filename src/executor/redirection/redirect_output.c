/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:14:55 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:12:56 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** open_output_file
**
** This function opens an output file for redirection.
** - Validate that the next token exists and is a TK_WORD
**   (the filename).
**     * If not, print a syntax error and return -1.
** - Set the filename to the value of the next token.
** - Choose flags depending on the redirection type:
**     * TK_OUT: write-only, create if needed, truncate file.
**     * TK_APPEND: write-only, create if needed, append mode.
** - Open the file with permissions 0644.
**     * If open() fails, print error and return -1.
** - Return the new file descriptor on success.
*/
int	open_output_file(t_token *curr, char **filename)
{
	int	flags;
	int	new_fd;

	if (curr->next == NULL || curr->next->type != TK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		return (-1);
	}
	*filename = curr->next->value;
	if (curr->type == TK_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	new_fd = open(*filename, flags, 0644);
	if (new_fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	return (new_fd);
}

/*
** setup_output_redirection
**
** This function applies an output redirection.
** - If file_fd == -1, return immediately (no redirection).
** - Save the current STDOUT with dup().
**     * If it fails, close file_fd, restore input redirection,
**       and return -1.
** - Duplicate file_fd into STDOUT using dup2().
**     * If it fails, close both file_fd and saved_fd, restore
**       input redirection, and return -1.
** - Close the file_fd after duplication.
** - Store saved_fd in shell->saved_stdout for later restore.
** - Return 0 on success.
*/
int	setup_output_redirection(int file_fd, t_shell *shell)
{
	int	saved_fd;

	if (file_fd == -1)
		return (0);
	saved_fd = dup(1);
	if (saved_fd == -1)
	{
		perror("minishell");
		close(file_fd);
		restore_input_redirection(shell);
		return (-1);
	}
	if (dup2(file_fd, 1) == -1)
	{
		perror("minishell");
		close(file_fd);
		close(saved_fd);
		restore_input_redirection(shell);
		return (-1);
	}
	close(file_fd);
	shell->saved_stdout = saved_fd;
	return (0);
}

/*
** handle_new_output_fd
**
** This helper function manages a new output file descriptor.
** - If new_fd is invalid (-1):
**     * Close any existing file_fd.
**     * Restore input redirection (to keep consistency).
**     * Return -1.
** - Otherwise:
**     * Close the previous file_fd if it was valid.
**     * Update file_fd with new_fd.
**     * Update shell->redirect_type with the current token type.
** - Return 0 on success.
*/
static int	handle_new_output_fd(int new_fd, int *file_fd,
								t_shell *shell, t_token *curr)
{
	if (new_fd == -1)
	{
		if (*file_fd != -1)
			close(*file_fd);
		restore_input_redirection(shell);
		return (-1);
	}
	if (*file_fd != -1)
		close(*file_fd);
	*file_fd = new_fd;
	shell->redirect_type = curr->type;
	return (0);
}

/*
** handle_output_redirection_token
**
** This function processes all output redirection tokens.
** - Traverse the token list:
**     * If the token is TK_OUT or TK_APPEND:
**         - Open the output file with open_output_file().
**         - Pass the new descriptor to handle_new_output_fd().
**         - If it fails, return -1.
** - After processing all tokens:
**     * Apply the final redirection with setup_output_redirection().
**         - If it fails, return -1.
** - Return 0 on success.
*/
int	handle_output_redirection_token(t_token *tokens, t_shell *shell)
{
	t_token	*curr;
	int		file_fd;
	char	*filename;
	int		new_fd;

	curr = tokens;
	file_fd = -1;
	while (curr != NULL)
	{
		if (curr->type == TK_OUT || curr->type == TK_APPEND)
		{
			new_fd = open_output_file(curr, &filename);
			if (handle_new_output_fd(new_fd, &file_fd, shell, curr) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	if (setup_output_redirection(file_fd, shell) == -1)
		return (-1);
	return (0);
}
