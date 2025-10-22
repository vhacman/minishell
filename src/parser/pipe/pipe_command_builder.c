/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command_builder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:57:40 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:16:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** extract_command_tokens
**
** This function extracts tokens for a single command until
** a pipe token (TK_PIPE) or end of list.
** - Allocate new tokens with create_token().
** - Link them into a new token list (cmd_tokens).
** - If allocation fails, free the partially built list.
** - Return the head of the new token list.
*/
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

/*
** setup_command_type_and_path
**
** This function determines whether a command is a builtin
** or an external command.
** - If args is empty, return 1 (invalid command).
** - If the command is builtin:
**     * Mark is_builtin = 1.
**     * Path is set to NULL.
** - Otherwise:
**     * Mark is_builtin = 0.
**     * Find the command path with find_command_path().
**     * If path not found, cleanup_per_command() is called
**       and path is set to NULL.
** - Always return 1.
*/
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
	}
	return (1);
}

/*
** create_and_populate_cmd
**
** This function creates and initializes a new command struct.
** - Allocate a new t_cmd with create_new_cmd().
** - Extract tokens for this command with extract_command_tokens().
** - Convert tokens into args using prepare_cmd_args().
** - If any step fails, free allocated resources and return NULL.
** - Store args and tokens inside the new command.
** - Call setup_command_type_and_path() to classify the command.
** - Return the new populated command structure.
*/
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

/*
** process_single_command
**
** This function processes one command in a pipeline.
** - Create and populate a new command from current_token.
** - Add it to the command list (head or next of last_command).
** - Advance current_token until a pipe is reached or list ends.
** - Skip the pipe token if present and continue.
** - Return the new command.
*/
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

/*
** convert_tokens_to_cmd_list
**
** This function converts a token list into a linked list
** of commands (t_cmd).
** - Initialize head and last_command pointers to NULL.
** - While tokens remain:
**     * Call process_single_command() to create a command.
**     * If creation fails, cleanup_per_command() and return NULL.
** - Return the head of the created command list.
*/
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
