/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:54 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:09:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** check_for_pipes
**
** This function scans the token list to see if there are
** any pipe operators ("|").
** - Iterate through all tokens.
** - If a token of type TK_PIPE is found, return 1 (true).
** - If no pipe token is found, return 0 (false).
*/
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

/*
** create_new_cmd
**
** This function allocates and initializes a new command node.
** - Allocate memory for a t_cmd structure.
** - Set default values:
**     * args and path to NULL.
**     * fd_in to STDIN_FILENO.
**     * fd_out to STDOUT_FILENO.
**     * next to NULL (no next command).
**     * type to 0.
** - Return the newly created command node.
** - If allocation fails, return NULL.
*/
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

/*
** check_syntax_pipes
**
** This function validates the correct syntax of pipes ("|").
** - If the first token is a pipe, return a syntax error.
** - Iterate through the token list:
**     * If two consecutive pipes are found, return an error.
** - If the last token is a pipe, return an error.
** - If no invalid cases are found, return 0 (valid syntax).
*/
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
