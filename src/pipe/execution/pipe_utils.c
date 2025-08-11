/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:54 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 15:11:26 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//HEADER CAMBIA IN BENIAMINO

#include "../../../include/minishell.h"

int	check_for_pipes(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_PIPE)
			return (1);
		curr = curr->next;
	}
	return (0);
}

t_cmd	*create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->path = NULL;
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->next = NULL;
	new_cmd->type = 0;
	return (new_cmd);
}

int	print_pipe_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	return (1);
}

int	check_syntax_pipes(t_token *tokens)
{
	t_token	*prev;
	t_token	*curr;

	if (!tokens)
		return (0);
	prev = NULL;
	curr = tokens;
	if (curr->type == TK_PIPE)
		return (print_pipe_error());
	while (curr)
	{
		if (curr->type == TK_PIPE && prev && prev->type == TK_PIPE)
			return (print_pipe_error());
		prev = curr;
		curr = curr->next;
	}
	if (prev && prev->type == TK_PIPE)
		return (print_pipe_error());
	return (0);
}
