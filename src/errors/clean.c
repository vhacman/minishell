/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:21:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 18:03:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->path)
		free(cmd->path);
	free(cmd);
}

void free_cmd_list(t_cmd **cmds)
{
	t_cmd *current = *cmds;
	t_cmd *next;

	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next;
	}
	*cmds = NULL;
}

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

void	free_args_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_parts(char *a, char *b, char *c)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free_parts(node->key, node->value, NULL);
	free(node);
}

void cleanup(t_shell *shell, int full_cleanup)
{
	if (!shell)
		return;
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
	if (full_cleanup)
	{
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
}

void	cleanup_and_exit(t_shell *shell, char **args, int exit_code)
{
	(void)args;
	cleanup(shell, 1);
	exit(exit_code);
}
