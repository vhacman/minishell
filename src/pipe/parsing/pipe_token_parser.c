/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_token_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begiovan <begiovan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:56:35 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 17:30:40 by begiovan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
