/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:21:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 11:58:36 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
