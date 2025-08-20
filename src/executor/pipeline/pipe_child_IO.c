/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child_IO.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:46:25 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 13:56:07 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


//MODIFICATA PER INCLUDERE REDIREZIONI 
/* 
 * setup_child_pipes:
 * Configures stdin/stdout using the previous pipe (prev_fd)
 * and the current pipe (pipe_fd) if necessary.
 */
static void	setup_child_pipes(t_cmd *curr, int prev_fd, int *pipe_fd)
{
	int	has_input_redir;
	int	has_output_redir;

	// Gestisci input dal comando precedente
	if (prev_fd != -1)
	{
		has_input_redir = has_input_redirection(curr->tokens);
		if (!has_input_redir)
			dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	
	// Gestisci output verso comando successivo
	if (curr->next && pipe_fd)
	{
		has_output_redir = has_output_redirection(curr->tokens);
		
		// Chiudi sempre il lato lettura nel processo che scrive
		close(pipe_fd[0]);
		
		if (!has_output_redir)
		{
			// Se non c'è redirezione di output, usa la pipe
			dup2(pipe_fd[1], STDOUT_FILENO);
		}
		// Se c'è redirezione di output, non fare dup2 ma lascia che 
		// la redirezione gestisca l'output
		
		// Chiudi sempre il lato scrittura dopo dup2 (o comunque)
		close(pipe_fd[1]);
	}
}

/* 
 * setup_child_redir_and_signals:
 * Applies redirections defined by tokens and 
 * sets child process signal handlers.
 */
static void	setup_child_redir_and_signals(t_cmd *curr, t_shell *shell)
{
	if (curr->tokens)
	{
		if (handle_redirection_with_tokens(curr->tokens, shell) == -1)
		{
			destroy_shell(shell);
			exit(1);
		}
	}
	setup_signals_child();
}

/* 
 * setup_child_io_and_signals:
 * Entry point combining pipes setup and
 * redirections/signals configuration.
 */
void	setup_child_io_and_signals(t_cmd *curr,
					int prev_fd, int *pipe_fd, t_shell *shell)
{
	setup_sigpipe_handling();
	setup_child_pipes(curr, prev_fd, pipe_fd);
	setup_child_redir_and_signals(curr, shell);
}
