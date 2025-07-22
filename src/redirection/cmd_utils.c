/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:15 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/22 13:57:27 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//alloca memoria per un nuovo t_token, duplica la stringa value, imposta
//next a NULL, se qualcosa va storto libera la memoria e restituisce NULL
//quando costruisco sotto liste di token per ogni comando (per isolare i token fra le due pipe)
//non bisogna modificare la lista originale, quindi clono ogni nodo cosi' posso montare una lista 
//pulita per l'esecuzione di ogni comando. 
static t_token	*clone_token(const t_token *src)
{
	t_token	*dest;

	dest = malloc(sizeof(t_token));
	if (!dest)
		return (NULL);
	dest->value = ft_strdup(src->value);
	if (!dest->value)
	{
		free(dest);
		return (NULL);
	}
	dest->type = src->type;
	dest->next = NULL;
	return (dest);
}

//prende un token src, lo clona e lo aggiunge in fondo ad una lista
//se la lista e' vuota (*head ==NULL), il nuovo token diventa sia inizio
//che fine della lista, altrimenti viene collegato alla fine della lista corrente.
//se il clone fallisce, restituisce NULL
//Serve per costruire una lista pulita per ogni singolo comando.
//infatti durante il parsinf dei comangi voglio costruire per ogni comando
// la sua propria lista di token. Quindi questa funzione ci permette di accodare uno a uno i token clonati. 
static t_token	*append_clone_token(t_token **head, t_token **tail,
									t_token *src_token)
{
	t_token	*new_token;

	new_token = clone_token(src_token);
	if (!new_token)
		return (NULL);
	if (!*head)
	{
		*head = new_token;
		*tail = new_token;
	}
	else
	{
		(*tail)->next = new_token;
		*tail = new_token;
	}
	return (new_token);
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
		if (!append_clone_token(&new_list, &new_tail, curr))
			return (free_token_list(new_list), NULL);
		curr = curr->next;
	}
	return (new_list);
}
