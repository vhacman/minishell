/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:12:15 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:12:30 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	open_input_file(t_token *curr, t_shell *shell)
{
	char	*filename;

	filename = curr->next->value;
	return (open_file_by_type(filename, curr->type, shell));
}

void	restore_input_redirection(t_shell *shell)
{
	if (shell->saved_stdin >= 0)
	{
		dup2(shell->saved_stdin, 0);
		close(shell->saved_stdin);
		shell->saved_stdin = -1;
	}
}

void	update_input_fd(int *input_fd, int new_input_fd)
{
	if (*input_fd != -1)
		close(*input_fd);
	*input_fd = new_input_fd;
}

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
