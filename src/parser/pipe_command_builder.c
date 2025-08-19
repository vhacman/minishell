/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command_builder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:57:40 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/19 17:00:30 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
** Estrae una sottolista di token da start fino al primo TK_PIPE (escluso)
** o fino alla fine della lista se non ci sono pipe.
*/
static t_token *extract_command_tokens(t_token *start)
{
	t_token *cmd_tokens = NULL;
	t_token *last_token = NULL;
	t_token *curr = start;
	
	while (curr && curr->type != TK_PIPE)
	{
		t_token *new_token = create_token(curr->value, curr->type);
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
** Determines if the command is a built-in or an external program,
** and sets the appropriate execution path.
** 1. If there are no arguments (`args[0]` is NULL), return immediately.
** 2. If the first argument matches a built-in command:
**      - Mark `is_builtin` as true.
**      - Set `path` to NULL (no need to search the filesystem).
** 3. Otherwise:
**      - Mark `is_builtin` as false.
**      - Search for the executable path using `find_command_path`.
**      - If no path is found:
**          - Call `cleanup_per_command` to free resources.
**          - Ensure `path` is set to NULL.
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
		if (!cmd->path)
		{
			cleanup_per_command(shell);
			cmd->path = NULL;
		}
	}
	return (1);
}

/*
** Creates a new command structure and fills it with data from tokens.
** 1. Allocate a new `t_cmd` structure using `create_new_cmd`.
**      - If allocation fails, return NULL.
** 2. Populate its arguments from the given token list
**    using `populate_command_args`.
**      - On failure, free the allocated command,
**        clean up per-command resources, and return NULL.
** 3. Determine if the command is a built-in or an external program,
**    and set its execution path with `setup_command_type_and_path`.
** 4. Return the fully prepared `t_cmd` structure.
*/
static t_cmd	*create_and_populate_cmd(t_token *token_start, t_shell *shell)
{
	t_cmd	*new_command;
	t_token *cmd_tokens;

	new_command = create_new_cmd();
	if (!new_command)
		return (NULL);
	// Estrae i token per questo comando (fino alla pipe o fine lista)
	cmd_tokens = extract_command_tokens(token_start);
	if (!cmd_tokens)
	{
		free_cmd(new_command);
		return (NULL);
	}
	// Usa le stesse funzioni dei comandi singoli per gestire redirezioni
	new_command->args = prepare_cmd_args(cmd_tokens, shell);
	if (!new_command->args)
	{
		free_token_list(&cmd_tokens);
		free_cmd(new_command);
		return (NULL);
	}
	// Gestisce le redirezioni per questo comando specifico
	// Nota: le redirezioni vengono applicate durante l'esecuzione del child process
	new_command->tokens = cmd_tokens; // Salva i token per dopo
	setup_command_type_and_path(new_command, shell);
	return (new_command);
}

/*
** Processes a sequence of tokens into a single command structure.
** 1. Create and populate a `t_cmd` from the current token position.
**      - On failure, return NULL.
** 2. Append the new command to the command list:
**      - If list is empty, set it as the head.
**      - Otherwise, link it after the last command.
** 3. Advance the token pointer until a pipe token (TK_PIPE) is found.
** 4. If a pipe is found, skip it and move to the next token.
** 5. Return the newly created command.
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
	// Avanza fino alla pipe successiva
	while (*current_token && (*current_token)->type != TK_PIPE)
		*current_token = (*current_token)->next;
	if (*current_token)
		*current_token = (*current_token)->next;
	return (new_command);
}

/*
** Converts a token list into a linked list of commands.
** 1. Initialize an empty command list (head and last command as NULL).
** 2. Iterate through the token list starting from the first token.
** 3. For each segment of tokens (until a pipe):
**      - Call process_single_command() to create and append a t_cmd.
**      - On failure, clean up command data and return NULL.
** 4. Continue until all tokens are processed.
** 5. Return the head of the created command list.
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
