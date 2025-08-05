/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_for_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:37:03 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 18:00:51 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_for_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:37:03 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 16:54:48 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_cmd *create_and_populate_cmd(t_token *start, t_shell *shell)
{
	t_cmd		*new_cmd;
	t_token		*tmp;
	int			count;
	int			i;

	new_cmd = create_new_cmd();
	if (!new_cmd)
		return (NULL);
	count = 0;
	tmp = start;
	while (tmp && tmp->type != TK_PIPE)
	{
		count++;
		tmp = tmp->next;
	}
	if (count == 0)
	{
		cleanup(shell, 1);
		return (NULL);
	}
	new_cmd->args = calloc((count + 1), sizeof(char *));
	if (!new_cmd->args)
	{
		cleanup(shell, 1);
		return (NULL);
	}
	tmp = start;
	i = 0;
	while (tmp && tmp->type != TK_PIPE)
	{
		new_cmd->args[i] = ft_strdup(tmp->value);
		if (!new_cmd->args[i])
		{
			while (--i >= 0)
				free(new_cmd->args[i]);
			free(new_cmd->args);
			free(new_cmd);
			cleanup(shell, 1);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	new_cmd->args[i] = NULL;
	if (new_cmd->args[0])
	{
		if (is_builtin(new_cmd->args[0]))
		{
			new_cmd->is_builtin = 1;
			new_cmd->path = NULL;
		}
		else
		{
			new_cmd->is_builtin = 0;
			new_cmd->path = find_command_path(new_cmd->args[0]);
			if (!new_cmd->path)
			{
				cleanup(shell, 1);
				new_cmd->path = NULL;
			}
		}
	}
	return (new_cmd);
}
t_cmd *convert_tokens_to_cmd_list(t_token *tokens, t_shell *shell)
{
	t_cmd		*cmd_list;
	t_cmd		*current_cmd;
	t_token		*cursor;
	t_cmd		*new_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	cursor = tokens;
	while (cursor)
	{
		new_cmd = create_and_populate_cmd(cursor, shell);
		if (!new_cmd)
		{
			cleanup(shell, 1);
			return (NULL);
		}
		if (!cmd_list)
			cmd_list = new_cmd;
		else
			current_cmd->next = new_cmd;
		current_cmd = new_cmd;
		while (cursor && cursor->type != TK_PIPE)
			cursor = cursor->next;
		if (cursor && cursor->type == TK_PIPE)
			cursor = cursor->next;
	}
	return (cmd_list);
}
