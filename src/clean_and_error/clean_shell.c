/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:21:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 15:41:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Frees all resources allocated during a single command
** execution, preparing the shell for the next prompt cycle.
**
** Steps:
** 1. If `shell` is NULL, exit immediately.
** 2. If `line` is set, free it and reset to NULL.
** 3. If `tokens` list exists, free it with
**    `free_token_list` and reset to NULL.
** 4. If `cmds` list exists, free it with `free_cmd_list`
**    and reset to NULL.
** This avoids memory leaks between command executions.
*/
void	cleanup_per_command(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (shell->tokens)
	{
		free_token_list(&shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmds)
	{
		free_cmd_list(&shell->cmds);
		shell->cmds = NULL;
	}
}

/*
** Frees all resources associated with the shell before exit.
**
** Steps:
** 1. If `shell` is NULL, do nothing.
** 2. Call `cleanup_per_command` to release resources used
**    by the last executed command.
** 3. If the environment list exists, free it with
**    `free_env_list` and reset to NULL.
** 4. If the program name is set, free it and reset to NULL.
** This ensures all dynamically allocated memory in the shell
** is released before termination.
*/
void	destroy_shell(t_shell *shell)
{
	if (!shell)
		return ;
	cleanup_per_command(shell);
	if (shell->env)
	{
		free_env_list(shell->env);
		shell->env = NULL;
	}
	if (shell->program_name)
	{
		free(shell->program_name);
		shell->program_name = NULL;
	}
}
