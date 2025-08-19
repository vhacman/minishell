/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:35:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/19 17:47:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	setup_command_execution(t_cmd *curr, int prev_fd, int *pipe_fd, pid_t *pid)
{
	(void)prev_fd;
	if (curr->next && pipe(pipe_fd) == -1)
		return (print_error("pipe"));
	*pid = fork();
	if (*pid == -1)
		return (print_error("fork"));
	return (0);
}

int	execute_single_command(t_cmd *curr, int prev_fd, int *pipe_fd,
		t_shell *shell)
{
	pid_t	pid;

	if (setup_command_execution(curr, prev_fd, pipe_fd, &pid) == 1)
		return (1);
	if (pid == 0)
		execute_child_process(curr, prev_fd, pipe_fd, shell);
	if (prev_fd != -1)
		close(prev_fd);
	if (curr->next)
		close(pipe_fd[1]);
	return (0);
}
