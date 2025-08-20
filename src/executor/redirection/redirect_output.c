/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:14:55 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:26:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
