/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:35:11 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/22 12:41:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/*in un processo figlio rialloca gli estremi della pipe sui file descripto standard.
se is_left si verifica siamo nel primo comando e quindi chiudiamo pipe_fd[0] (cioe il lato lettura perche non ci serve)
Successivamente redirige cond dup2 tutto quello che il processo scrive su stdout verso l-estremo di scrittura della pipe,
chiude poi la pipe_fd[1] originale.
se is_left == 0 siamo nel secondo comando, quindi chiudiamo pipe_fd[1] (lato scrittura), redirigiamo lo stdin del processo a leggere dall'estremo
di lettura della pipe e chiudiamo la pipe_fd[0] originale. 
*/
int	setup_child_pipe(int pipe_fd[2], int is_left)
{
	if (is_left)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(pipe_fd[1]);
			return (-1);
		}
		close(pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(pipe_fd[0]);
			return (-1);
		}
		close(pipe_fd[0]);
	}
	return (0);
}

/*LO scopo e' creare il primo processo figlio e farlo eseguire il comando cmd1, scrivendo sulla pipe
se fork() fallisce, pulisce la pipe, ripristina i segnali in modalità interattiva (setup_signals_interactive()) e ritorna -1.
Nel figlio (pid1 == 0) chiama setup_child_pipe(pipe_fd, 1) per ridirigere stdout verso la pipe 
Se setup_child_pipe non va a buon fine, esce con exit(1) altrimenti, lancia execute_cmd_in_pipe(cmd1, shell),
che invoca funzione del builtin (execute_cmd_in_pipe). nl padre: restituisce il PID del figlio,
così poi potrà fare waitpid su di lui.*/
int	fork_first_child(t_cmd *cmd1, t_shell *shell, int pipe_fd[2])
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		setup_signals_interactive();
		return (-1);
	}
	if (pid1 == 0)
	{
		if (setup_child_pipe(pipe_fd, 1) == -1)
			exit(1);
		execute_cmd_in_pipe(cmd1, shell);
	}
	return (pid1);
}

/*lo scopo e' creare il secondo processo figlio e farlo eseguire cmd2, leggendo dalla pipe.
Se fork() fallisce stampa l’errore, pulisce la pipe, manda SIGTERM al primo figlio (kill(pid1, SIGTERM)),
Attende la sua fine con waitpid, ripristina i segnali interattivi e ritorna -1.

Nel figlio (pid2 == 0) xhiama setup_child_pipe(pipe_fd, 0) per ridirigere stdin dalla pipe.
Se fallisce, esce con exit(1) e lancia execute_cmd_in_pipe(cmd2, shell).Nel padre: restituisce il PID del secondo figlio.*/
int	fork_second_child(t_cmd *cmd2, t_shell *shell, int pipe_fd[2], pid_t pid1)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		kill(pid1, SIGTERM);
		waitpid(pid1, NULL, 0);
		setup_signals_interactive();
		return (-1);
	}
	if (pid2 == 0)
	{
		if (setup_child_pipe(pipe_fd, 0) == -1)
			exit(1);
		execute_cmd_in_pipe(cmd2, shell);
	}
	return (pid2);
}
