/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 14:14:16 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int handle_null_tokens(t_shell *shell)
{
	ft_putstr_fd("minishell: : command not found\n", 2);
	shell->exit_status = 127;
	return (127);
}

char **prepare_cmd_args(t_token *tokens, t_shell *shell)
{
	char **args;

	args = create_args_without_redirection(tokens);
	if (!args)
	{
		cleanup_per_command(shell);
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->exit_status = 127;
		return (NULL);
	}
	if (!args[0])
	{
		free_args_array(args);
		cleanup_per_command(shell);
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->exit_status = 127;
		return (NULL);
	}
	return (args);
}

int setup_redirection(t_token *tokens, char **args, t_shell *shell)
{
	if (handle_redirection_with_tokens(tokens, shell) == -1)
	{
		free_args_array(args);
		cleanup_per_command(shell);
		shell->exit_status = 1;
		return (-1);
	}
	return (0);
}
