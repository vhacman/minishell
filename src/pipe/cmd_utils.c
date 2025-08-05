/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:15 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 10:17:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//prende un token src, lo clona e lo aggiunge in fondo ad una lista
//se la lista e' vuota (*head ==NULL), il nuovo token diventa sia inizio
//che fine della lista, altrimenti viene collegato alla fine della lista corrente.
//se il clone fallisce, restituisce NULL
//Serve per costruire una lista pulita per ogni singolo comando.
//infatti durante il parsinf dei comangi voglio costruire per ogni comando
// la sua propria lista di token. Quindi questa funzione ci permette di accodare uno a uno i token clonati.
static t_token	*append_token(t_token **head, t_token **tail,
									t_token *src_token)
{
	if (!src_token)
		return NULL;
	src_token->next = NULL;
	if (!*head)
	{
		*head = src_token;
		*tail = src_token;
	}
	else
	{
		(*tail)->next = src_token;
		*tail = src_token;
	}
	return src_token;
}

/*
quando hai una lista di token per un comando tipo
ls -l | grep txt | wc -l
questa funzione serve per isolare ogni comando a se, quindi da ls fino alla prima |
poi da grep alla seconda | e poi wc -l
permette dunque di generare, senza toccare la lista originale, una sottolista indipendente
di token per ciascun comando nella pipeline. */
t_token	*create_token_sublist(t_token *start, t_token *end)
{
	t_token	*new_list;
	t_token	*new_tail;
	t_token	*curr;

	new_list = NULL;
	new_tail = NULL;
	curr = start;
	while (curr && curr != end)
	{
		if (!append_token(&new_list, &new_tail, curr))
			return (free_token_list(&new_list), NULL);
		if (curr == end)
			break ;
		curr = curr->next;
	}
	return (new_list);
}
