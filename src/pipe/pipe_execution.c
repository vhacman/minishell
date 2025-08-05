/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:50 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 12:05:51 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*finche c'e un comando e non ci sono errori, chiama execute_single_command che serve a creare
una nuova pipe, fa fork, nel figlio ridirige prev_fd su stdin e il nuovo pipe_fd[1] su stdout
esefue il comando

Se c’è un comando successivo (curr->next), 
il lato di lettura della pipe (pipe_fd[0]) diventa il prev_fd per il comando seguente.

Se l’errore è avvenuto dopo aver creato almeno una pipe,
chiude prev_fd per non lasciare descriptor aperti.
*/
static int	execute_commands_loop(t_cmd *cmds, t_shell *shell)
{
	int		pipe_fd[2];
	int		prev_fd;
	t_cmd	*curr;
	int		error_occurred;

	prev_fd = -1;
	curr = cmds;
	error_occurred = 0;
	while (curr && !error_occurred)
	{
		if (execute_single_command(curr, prev_fd, pipe_fd, shell) != 0)
		{
			error_occurred = 1;
			break ;
		}
		if (curr->next)
			prev_fd = pipe_fd[0];
		else
			prev_fd = -1;
		curr = curr->next;
	}
	if (error_occurred && prev_fd != -1)
		close(prev_fd);
	return (error_occurred);
}

/*chiama ripetutamente wait(&status) finche ci sono processi figli in esecuzione, calcola lo exit status
finale. se il figlio e' terminato normalmente imposta shell->exit_status al codice di uscita (0-255)
se e' terminato per segnale lo marca come 128 + numero del segnale come da bash*/
static int	wait_for_children(t_shell *shell)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
	}
	return (shell->exit_status);
}

/*prepara i segnali, crea ed esegue i comandi con execute_commands_loop per far apparire tutit i figli in serie collegandoli alla pipe
se fallisce ripristina i segnali interattivi e ritorna 1
altrimenti chiuama wait_for_children per attendere e raccogliere gli exit status di tutti i figli. 
Con setup_signals_interactive(), rimette la shell nel suo normale handling di Ctrl‑C, Ctrl‑Z, prompt ecc.
*/
int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int	error_occurred;

	setup_signals_executing();
	error_occurred = execute_commands_loop(cmds, shell);
	if (error_occurred)
	{
		setup_signals_interactive();
		return (1);
	}
	wait_for_children(shell);
	setup_signals_interactive();
	return (shell->exit_status);
}
