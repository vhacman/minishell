/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_token_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:56:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:30:33 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Counts the number of tokens from the given start token until
** a pipe token (TK_PIPE) or the end of the list is reached.
** This is used to determine the argument count for a single
** command segment in a pipeline.
*/
static int	count_args_until_pipe(t_token *token_start)
{
	t_token	*token_cursor;
	int		arg_count;

	arg_count = 0;
	token_cursor = token_start;
	while (token_cursor && token_cursor->type != TK_PIPE)
	{
		arg_count++;
		token_cursor = token_cursor->next;
	}
	return (arg_count);
}

/*
** Allocates memory for the command's argument array based on the
** given argument count. An extra slot is reserved for a NULL
** terminator as required by execve().
** - command: Pointer to the command structure where args is set.
** - arg_count: Number of argument strings to allocate space for.
*/
static int	alloc_args_array(t_cmd *command, int arg_count)
{
	if (arg_count == 0)
		return (0);
	command->args = calloc((arg_count + 1), sizeof(char *));
	if (!command->args)
		return (0);
	command->args[arg_count] = NULL;
	return (1);
}

/*
** Copies token values into the command's argument array until a
** pipe token or the end of the list is reached. Each token value
** is duplicated to avoid dependency on the original token list.
** - command: Pointer to the command structure to fill.
** - token_start: First token to process for arguments.
*/
static int	fill_args_until_pipe(t_cmd *command, t_token *token_start)
{
	t_token	*token_cursor;
	int		arg_index;

	token_cursor = token_start;
	arg_index = 0;
	while (token_cursor && token_cursor->type != TK_PIPE)
	{
		command->args[arg_index] = ft_strdup(token_cursor->value);
		if (!command->args[arg_index])
		{
			while (--arg_index >= 0)
				free(command->args[arg_index]);
			free(command->args);
			command->args = NULL;
			return (0);
		}
		arg_index++;
		token_cursor = token_cursor->next;
	}
	return (1);
}

/*
** Populates a t_cmd structure with arguments extracted from a token list,
** starting at 'token_start' and stopping at the first pipe token (TK_PIPE).
**  1. Count the number of arguments until a pipe is reached.
**  2. Allocate memory for the args array (+1 for the NULL terminator).
**  3. Copy each token's value into the args array until the pipe.
*/
int	populate_command_args(t_cmd *command, t_token *token_start)
{
	int	arg_count;

	arg_count = count_args_until_pipe(token_start);
	if (!alloc_args_array(command, arg_count))
		return (0);
	if (!fill_args_until_pipe(command, token_start))
		return (0);
	return (1);
}
