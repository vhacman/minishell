/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_for_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:37:03 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/21 16:38:16 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
Crea un nuovo nodo t_cmd vuoto, clona i token che vanno da cmd_start fino a curr (se curr e' una pipe),
converte i token in un array di stringhe (char **args) e libera la lista temporanea di token, restituisce infinte il t_cmd popolato
E' utile perche' unisce il flusso di creazione del comando:
alloca la struttura t_cmd
isola e clona i token rilevati
converte in args
pulise
cosi' creo sempre un nodo t_cmd indipendente, pronto per essere collegato alla lista*/
static t_cmd	*create_and_populate_cmd(t_token *cmd_start, t_token *curr)
{
	t_cmd	*new_cmd;
	t_token	*temp_tokens;

	new_cmd = create_new_cmd();
	if (!new_cmd)
		return (NULL);
	if (curr->type == TK_PIPE)
		temp_tokens = create_token_sublist(cmd_start, curr);
	else
		temp_tokens = create_token_sublist(cmd_start, NULL);
	if (temp_tokens)
	{
		new_cmd->args = convert_tokens_to_args(temp_tokens);
		free_token_list(temp_tokens);
	}
	return (new_cmd);
}

/*
Collgea un nuovo nodo t_cmd alla lista di comandi in costruzione
Nel parsing dei token, mano a mano che identifico un comando completo (tramite create_and_populate_cmd) devo inserilo
in una lista concatenata di t_cmd
cmd_list punta sempre all'inizio della lista intera, cosi poi la possiamo restituire o scorrere
current_cmd tiene traccia dell'ultimo inserito, cosi possiamo appendere il prossimo*/
static void	add_cmd_to_list(t_cmd *new_cmd, t_cmd **cmd_list,
		t_cmd **current_cmd)
{
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		*current_cmd = new_cmd;
	}
	else
	{
		(*current_cmd)->next = new_cmd;
		*current_cmd = new_cmd;
	}
}

/*questa funzione capisce dove fermars quando parso la sequenza di token. quindi qui
troviamo il token confine. 
quindi in convert_tokens_to_commands si puo: trovare un delimitatore, clonare i token tra l'inizio del comando 
e il delimitatore, creare il t_cmd e attaccarlo alla lista, per poi ripartire dal token successivo al delimitatore*/
static t_token	*find_next_cmd_delimiter(t_token *start)
{
	t_token	*curr;

	curr = start;
	while (curr)
	{
		if (curr->type == TK_PIPE || !curr->next)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/*Nel ciclo che scorre i token all’interno di convert_tokens_to_commands, 
ogni volta che trova un delimitatore (pipe o fine lista) viene chiamata questa funzione:
prende i token del comando corrente, trasforma in t_cmd e li appende alla lista*/
static int	process_command_tokens(t_token *cmd_start, t_token *delimiter,
		t_cmd **cmd_list, t_cmd **current_cmd)
{
	t_cmd	*new_cmd;

	new_cmd = create_and_populate_cmd(cmd_start, delimiter);
	if (!new_cmd)
		return (0);
	add_cmd_to_list(new_cmd, cmd_list, current_cmd);
	return (1);
}

/*Trasforma una lista concatenata di token (eventualmente contenente simboli di pipe)
 in una lista concatenata di strutture t_cmd, ognuna delle quali rappresenta un singolo
 comando da eseguire (con il proprio array di argomenti e tutte le informazioni necessarie).
 Conclude il parsing della pipeline, da sequenza di token a sequenza di comandi eseguibili.*/
t_cmd	*convert_tokens_to_cmd_list(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_token	*cmd_start;
	t_token	*delimiter;

	if (!tokens)
		return (NULL);
	cmd_list = NULL;
	current_cmd = NULL;
	cmd_start = tokens;
	while (cmd_start)
	{
		delimiter = find_next_cmd_delimiter(cmd_start);
		if (!delimiter)
			break ;
		if (!process_command_tokens(cmd_start, delimiter, &cmd_list,
				&current_cmd))
			return (NULL);
		if (delimiter->type == TK_PIPE)
			cmd_start = delimiter->next;
		else
			break ;
	}
	return (cmd_list);
}
