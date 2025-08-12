/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:55:06 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:04:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_child_io_and_signals(t_cmd *curr, int prev_fd, int *pipe_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (curr->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	setup_signals_child();
}

static void	execute_builtin_child(t_cmd *curr, t_shell *shell)
{
	int	status;

	status = handle_builtin(curr->args, shell);
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
		destroy_shell(shell);
		exit(127);
	}
	envp = build_envp_from_list(shell->env);
	if (!envp)
	{
		destroy_shell(shell);
		exit_with_error("malloc", NULL, 0, 1);
	}
	if (execve(curr->path, curr->args, envp) == -1)
	{
		free_args_array(envp);
		destroy_shell(shell);
		exit_with_error("execve", NULL, 0, 1);
	}
}

void	execute_child_process(t_cmd *curr, int prev_fd,
								int *pipe_fd, t_shell *shell)
{
	setup_child_io_and_signals(curr, prev_fd, pipe_fd);
	if (curr->is_builtin)
		execute_builtin_child(curr, shell);
	else
		execute_system_command(curr, shell);
}
