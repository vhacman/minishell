/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command_builder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:57:40 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 15:47:58 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	setup_command_type_and_path(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->args[0])
		return (1);
	if (is_builtin(cmd->args[0]))
	{
		cmd->is_builtin = 1;
		cmd->path = NULL;
	}
	else
	{
		cmd->is_builtin = 0;
		cmd->path = find_command_path(cmd->args[0], shell);
		if (!cmd->path)
		{
			cleanup_per_command(shell);
			cmd->path = NULL;
		}
	}
	return (1);
}

static t_cmd	*create_and_populate_cmd(t_token *token_start, t_shell *shell)
{
	t_cmd	*new_command;

	new_command = create_new_cmd();
	if (!new_command)
		return (NULL);
	if (!populate_command_args(new_command, token_start))
	{
		free_cmd(new_command);
		cleanup_per_command(shell);
		return (NULL);
	}
	setup_command_type_and_path(new_command, shell);
	return (new_command);
}

static t_cmd	*process_single_command(t_token **current_token, t_shell *shell,
								t_cmd **command_list_head, t_cmd **last_command)
{
	t_cmd	*new_command;

	new_command = create_and_populate_cmd(*current_token, shell);
	if (!new_command)
		return (NULL);
	if (!*command_list_head)
		*command_list_head = new_command;
	else
		(*last_command)->next = new_command;
	*last_command = new_command;
	while (*current_token && (*current_token)->type != TK_PIPE)
		*current_token = (*current_token)->next;
	if (*current_token && (*current_token)->type == TK_PIPE)
		*current_token = (*current_token)->next;
	return (new_command);
}

t_cmd	*convert_tokens_to_cmd_list(t_token *token_list, t_shell *shell)
{
	t_cmd	*command_list_head;
	t_cmd	*last_command;
	t_token	*current_token;

	command_list_head = NULL;
	last_command = NULL;
	current_token = token_list;
	while (current_token)
	{
		if (!process_single_command(&current_token, shell,
				&command_list_head, &last_command))
		{
			cleanup_per_command(shell);
			return (NULL);
		}
	}
	return (command_list_head);
}
