/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:36 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/04 18:05:09 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Crea il canale di comunicazione tra i due processi figli
inizializza pipe_fd[0] per la lettura e pipe_fd[1] per la scrittura.
CHiama setup_signals_executing che disabilita il comportamento di alcuni segnali
nei processi figli, per evitare che interferiscano con la shell padre(esempio ctrl+c)*/
int	create_pipe_and_setup(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (1);
	setup_signals_executing();
	return (0);
}

/*Esegue un comando dentro una pipe
Se la struttura del comando e' malformata(manca o e' vuota) stampa errore ed esce
Se il comando e' una builtin lo esegue direttamente e termina con il suo 
valore di ritorno
Altrimenti cerca il persorso eseguibile del comando. se non lo trova stampa errore
ed esce, se lo trova lo esegue come comando esterno, libera la memoria allocata
per il path e ritorna lo status dell'esecuzione.
*/
int	execute_cmd_in_pipe(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		print_error("minishell: command structure error");
		return (1);
	}
	if (is_builtin(cmd->args[0]))
		return (handle_builtin(cmd->args, shell));
	cmd_path = find_command_path(cmd->args[0]);
	if (!cmd_path)
		return (print_error(cmd->args[0]), 127);
	status = execute_external_command(cmd_path, cmd->args, shell);
	free(cmd_path);
	exit(status);
}

/*Gestisce l'esecuzione di due comandi collegati da una pipe. controlla che
cmd1, cmd2 e shell non siano null
crea la pipe, fa fork del primo figlio (che esegue cmd1 che scrive nella pipe)
fa fork() del secondo giglio (che esegue cmd2, legge dalla pipe), chiude le due estremita'
della pipe nel processo padre.
Aspetta che entrambi i figli finiscono (waitpid), gestisce eventuali terminazioni da segnale e 
aggiorna exit status
reiposta i segnali interativi per utente. */
int	handle_pipe(t_cmd *cmd1, t_cmd *cmd2, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (!cmd1 || !cmd2 || !shell)
		return (print_error("Error: pipe"));
	if (create_pipe_and_setup(pipe_fd) != 0)
		return (1);
	pid1 = fork_first_child(cmd1, shell, pipe_fd);
	if (pid1 == -1)
		return (-1);
	pid2 = fork_second_child(cmd2, shell, pipe_fd, pid1);
	if (pid2 == -1)
		return (1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	handle_signal_exit_status(status2, shell);
	setup_signals_interactive();
	return (shell->exit_status);
}
