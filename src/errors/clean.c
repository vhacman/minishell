/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:21:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 14:44:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
}

void free_token_list(t_token **token)
{
	t_token *tmp;

	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->value);
		free(*token);
		*token = tmp;
	}
}


void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free_parts(node->key, node->value, NULL);
	free(node);
}

void cleanup_per_command(t_shell *shell)
{
	if (!shell) return;
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

void destroy_shell(t_shell *shell)
{
	if (!shell) return;
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
