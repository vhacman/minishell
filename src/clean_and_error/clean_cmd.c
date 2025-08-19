/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:21:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/19 17:00:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Frees a NULL-terminated array of path strings.
**
** Steps:
** 1. If `paths` is NULL, return immediately.
** 2. Loop through each element until a NULL terminator:
**    - Free the string at the current index.
** 3. Free the array pointer itself after all strings
**    are released.
*/
void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

/*
** Frees a single command structure and its associated data.
**
** Steps:
** 1. If `cmd` is NULL, do nothing.
** 2. If `args` exists:
**    - Iterate through each argument string, freeing it.
**    - Free the `args` array itself.
** 3. If `path` is set, free it.
** 4. Finally, free the command structure.
** This ensures no memory leaks for a single command node.
*/
void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->path)
		free(cmd->path);
	if (cmd->tokens)
        free_token_list(&cmd->tokens);
    free(cmd);
}

/*
** Frees all nodes in a linked list of commands.
**
** Steps:
** 1. Start from the first command in the list.
** 2. For each command:
**    - Store the pointer to the next command in `next`.
**    - Free the current command using `free_cmd`, which
**      releases its internal resources.
**    - Move to the next command.
** 3. After freeing all commands, set the head pointer to NULL
**    to avoid dangling references.
*/
void	free_cmd_list(t_cmd **cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *cmds;
	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next;
	}
	*cmds = NULL;
}
