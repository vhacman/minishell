/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:55:06 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 18:45:33 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	execute_builtin_child(t_cmd *curr, t_shell *shell)
{
	int	status;

	status = handle_builtin(curr->args, shell);
	if (curr->tokens)
	{
		restore_redirection(shell);
		free_token_list(&curr->tokens);
	}
	destroy_shell(shell);
	exit(status);
}

static void	execute_system_command(t_cmd *curr, t_shell *shell)
{
	char		**envp;
	const char	*cmd;

	cmd = "";
	if (!curr->path)
	{
		if (curr->args && curr->args[0])
			cmd = curr->args[0];
		ft_printf("minishell: %s: command not found\n", cmd);
		cleanup_and_exit(curr, shell, 127);
	}
	envp = build_envp_from_list(shell->env);
	if (!envp)
	{
		cleanup_and_exit(curr, shell, 1);
	}
	if (execve(curr->path, curr->args, envp) == -1)
	{
		free_args_array(envp);
		cleanup_and_exit(curr, shell, 1);
	}
}

void	execute_child_process(t_cmd *curr, int prev_fd,
								int *pipe_fd, t_shell *shell)
{
	setup_child_io_and_signals(curr, prev_fd, pipe_fd, shell);
	if (curr->is_builtin)
		execute_builtin_child(curr, shell);
	else
		execute_system_command(curr, shell);
}
