/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: begiovan <begiovan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:02:46 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/06 15:33:31 by begiovan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_token_context(t_token_context *context, t_init_params *params)
{
	context->input = params->str;
	context->i = params->i;
	context->tokens = params->tokens;
	context->shell = params->shell;
	context->had_whitespace = 1;
}

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
	shell->saved_stdout = -1;
	shell->redirect_type = 0;

}
