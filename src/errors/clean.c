/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:21:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/21 13:34:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_cmd_list(t_cmd *cmds)
{
	t_cmd	*temp;

	while (cmds)
	{
		temp = cmds;
		cmds = cmds->next;
		free_split(temp->args);
		free(temp->path);
		free(temp);
	}
}

/*
**	Frees linked list of environment variables.
**
**	How it works		Iterates through env list, frees key, value, and node.
**	Params:				env	- pointer to head of env list
*/
static void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

/*
**	Frees linked list of tokens and their values.
**
**	How it works		Iterates through token list,
**						frees token->value if non-null, then node.
**	Params:				token	- pointer to head of token list
*/
void	free_token_list(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

/*
**	Frees an array of strings and the array itself.
**
**	How it works		Iterates over array until NULL,
*						frees each string, then frees the array pointer.
**	Params:		array	- NULL‑terminated array of malloc’d strings
*/
void	free_split(char **array)
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

/*
**	Frees three allocated strings.
**
**	How it works	Calls free on each pointer a, b, and c.
**	Params:		a	- first string to free
**				b	- second string to free
**				c	- third string to free
*/
void	free_parts(char *a, char *b, char *c)
{
	free(a);
	free(b);
	free(c);
}

/*
**	Cleans up shell resources.
**
**	How it works		Calls free_env_list on shell->env, frees shell->line,
**						free_token_list on shell->tokens,
**						and frees shell->program_name if set.
**	Params:		shell	- shell context with allocated fields
*/
void	cleanup(t_shell *shell)
{
	free_env_list(shell->env);
	if (shell->line)
		free(shell->line);
	if (shell->tokens)
		free_token_list(shell->tokens);
	if (shell->program_name)
		free (shell->program_name);
}
