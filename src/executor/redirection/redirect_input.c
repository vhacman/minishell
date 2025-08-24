/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:12:15 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:12:11 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** open_input_file
**
** This function opens the file specified for input redirection.
** - Get the filename from the token following the redirection
**   token (curr->next->value).
** - Call open_file_by_type() with the filename and redirection
**   type (TK_IN or TK_HEREDOC).
** - Return the resulting file descriptor or -1 on failure.
*/
int	open_input_file(t_token *curr, t_shell *shell)
{
	char	*filename;

	filename = curr->next->value;
	return (open_file_by_type(filename, curr->type, shell));
}


/*
** restore_input_redirection
**
** This function restores the original STDIN after an input
** redirection has been applied.
** - If a saved stdin file descriptor exists (>= 0):
**     * Restore it using dup2().
**     * Close the saved descriptor.
**     * Reset shell->saved_stdin to -1.
*/
void	restore_input_redirection(t_shell *shell)
{
	if (shell->saved_stdin >= 0)
	{
		dup2(shell->saved_stdin, 0);
		close(shell->saved_stdin);
		shell->saved_stdin = -1;
	}
}

/*
** update_input_fd
**
** This function updates the current input file descriptor.
** - If an old input_fd is active, close it to avoid leaks.
** - Replace it with new_input_fd.
*/
void	update_input_fd(int *input_fd, int new_input_fd)
{
	if (*input_fd != -1)
		close(*input_fd);
	*input_fd = new_input_fd;
}

/*
** handle_input_redirection_with_tokens
**
** This function processes all input redirection tokens in a
** command.
** - Initialize input_fd to -1 (no active redirection yet).
** - Traverse the token list:
**     * If a token is TK_IN ("<") or TK_HEREDOC ("<<"):
**         - Handle it with handle_single_input_redirect().
**         - If it fails, return -1.
** - After the loop:
**     * If input_fd is valid, apply the redirection using
**       apply_input_redirection().
**     * Otherwise, do nothing and return 0.
*/
int	handle_input_redirection_with_tokens(t_token *tokens, t_shell *shell)
{
	t_token		*curr;
	int			input_fd;

	curr = tokens;
	input_fd = -1;
	while (curr != NULL)
	{
		if (curr->type == TK_IN || curr->type == TK_HEREDOC)
		{
			if (handle_single_input_redirect(curr, shell, &input_fd) == -1)
				return (-1);
		}
		curr = curr->next;
	}
	if (input_fd != -1)
		return (apply_input_redirection(input_fd, shell));
	return (0);
}
