/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command_builder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:57:40 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 12:55:38 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_token	*extract_command_tokens(t_token *start)
{
	t_token	*cmd_tokens;
	t_token	*last_token;
	t_token	*curr;
	t_token	*new_token;

	cmd_tokens = NULL;
	last_token = NULL;
	curr = start;
	while (curr && curr->type != TK_PIPE)
	{
		new_token = create_token(curr->value, curr->type);
		if (!new_token)
		{
			free_token_list(&cmd_tokens);
			return (NULL);
		}
		if (!cmd_tokens)
			cmd_tokens = new_token;
		else
			last_token->next = new_token;
		last_token = new_token;
		curr = curr->next;
	}
	return (cmd_tokens);
}

static int	setup_command_type_and_path(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->args || !cmd->args[0])
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
	t_token	*cmd_tokens;

	new_command = create_new_cmd();
	if (!new_command)
		return (NULL);
	cmd_tokens = extract_command_tokens(token_start);
	if (!cmd_tokens)
	{
		free_cmd(new_command);
		return (NULL);
	}
	new_command->args = prepare_cmd_args(cmd_tokens, shell);
	if (!new_command->args)
	{
		free_token_list(&cmd_tokens);
		free_cmd(new_command);
		return (NULL);
	}
	new_command->tokens = cmd_tokens;
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
	if (*current_token)
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
			return (cleanup_per_command(shell), NULL);
	}
	return (command_list_head);
}
