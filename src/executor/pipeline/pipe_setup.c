/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:35:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 13:56:01 by vhacman          ###   ########.fr       */
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
		
	// Processo padre: chiudi i file descriptor appropriati
	if (prev_fd != -1)
		close(prev_fd);
		
	if (curr->next)
	{
		close(pipe_fd[1]);  // Chiudi sempre il lato scrittura nel padre
		
		// Se il comando corrente ha redirezione di output,
		// chiudi anche il lato lettura per evitare che il prossimo
		// comando rimanga bloccato
		if (has_output_redirection(curr->tokens))
			close(pipe_fd[0]);
	}
	
	return (0);
}	
