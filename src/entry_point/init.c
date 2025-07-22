/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:02:46 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 21:49:32 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Initialize the token context with given parameters.
** Assign input string, current index, token list, and shell pointer.
** Set had_whitespace flag to true for initial parsing state.
*/
void	init_token_context(t_token_context *context, t_init_params *params)
{
	context->input = params->str;
	context->i = params->i;
	context->tokens = params->tokens;
	context->shell = params->shell;
	context->had_whitespace = 1;
}

/*
** Initialize all shell structure fields to default values.
** Copy environment variables from extern environ into shell->env.
** Reset argument, command, and program name pointers to NULL.
*/
void	init_shell(t_shell *shell)
{
	extern char	**environ;

	shell->line = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->env = NULL;
	shell->exit_status = 0;
	shell->env = copy_env_entries(environ);
	shell->args = NULL;
	shell->program_name = NULL;
}
