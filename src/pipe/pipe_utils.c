/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:54 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 16:55:26 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//HEADER CAMBIA IN BENIAMINO

#include "../../include/minishell.h"

/*Controlla se nella lista di token c'e' almeno una pipe
scorre tutta la lista, se trova un token con tipo TK_PIPE restituisce 1
altrimenti, se arriva alla fkine senza trovarlo restituisce 0
*/
int	check_for_pipes(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_PIPE)
			return (1);
		curr = curr->next;
	}
	return (0);
}

/*
crea e inizializza una nuova struttura t_cmd. crea e inizializza una nuova struttura
, alloca memoria per un nuovo comando.
e' il punto di partenza per costruire una lista di comandi da eseguire.
*/
t_cmd	*create_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->path = NULL;
	new_cmd->fd_in = STDIN_FILENO;
	new_cmd->fd_out = STDOUT_FILENO;
	new_cmd->next = NULL;
	new_cmd->type = 0;
	return (new_cmd);
}

/*
Controlla se c'e' errore di sintassi, nell'uso delle pipe nei token
 Se la lista e' vuota, nessun errore. Se il primo token e' una pipe, errore
se ci sono due pipe consecutive, errore. se l'ultimo token e' pipe errore.
*/
int	check_syntax_pipes(t_token *tokens)
{
	t_token	*prev;
	t_token	*curr;

	if (!tokens)
		return (0);
	prev = NULL;
	curr = tokens;
	if (curr->type == TK_PIPE)
		return (print_pipe_error());
	while (curr)
	{
		if (curr->type == TK_PIPE && prev && prev->type == TK_PIPE)
			return (print_pipe_error());
		prev = curr;
		curr = curr->next;
	}
	if (prev && prev->type == TK_PIPE)
		return (print_pipe_error());
	return (0);
}
