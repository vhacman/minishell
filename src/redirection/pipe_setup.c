/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:35:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/22 12:52:19 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*Prepara per l'esecuzione del comando con la pipe.
Se il comando ha un next (quindi serve una pipe) crea la pipe_fd. se fallisce stampa errore 
e ritorna 1.
esegue fork() per creare il processo figlio, se fallisce stampa errore e torna q
se tutto va bene torna 0*/
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

/*Configura gli FD nel processo figlio per l'uso con la pipe,  oi esegue il comando. 
Se prev_fd e' valido (!= -1) reindirizza input standard da prev_fd poi lo chiude
se iul comando ha un next, chiude l'estremita' di lettura della nuova pipe, reindirizza
l'output standard sulla scrittura della pipe e poi chiude anche quella.
alla fine chiama execute_cmd_in_pipe per eseguire il comando.*/
int	handle_child_process(t_cmd *curr, int prev_fd, int *pipe_fd, t_shell *shell)
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
	execute_cmd_in_pipe(curr, shell);
	exit(1);
}

/*Esegue un singolo comando all'interno di una pipeline . chiama setup_command_execution
pre creare la pipe e il processo figlio. 
se siamo nel processo figlio (pid == 0) chiama handle_child_process per impostare gli FD e eseguire il comanfo
Se siamo nel padre chiude prev_fd se esiste xke non serve piu, chiude l'estremita' di scrittura
della pipe se c'e un comando successivo. 
SERVE PER ESECUZIONE COMANDO PER COMANDO NELLA PIPELINE*/
int	execute_single_command(t_cmd *curr, int prev_fd, int *pipe_fd,
		t_shell *shell)
{
	pid_t	pid;

	if (setup_command_execution(curr, prev_fd, pipe_fd, &pid) == 1)
		return (1);
	if (pid == 0)
		handle_child_process(curr, prev_fd, pipe_fd, shell);
	if (prev_fd != -1)
		close(prev_fd);
	if (curr->next)
		close(pipe_fd[1]);
	return (0);
}
