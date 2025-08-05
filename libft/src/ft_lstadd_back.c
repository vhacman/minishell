/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:44:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/04 13:44:01 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* La funzione aggiunge un nuovo nodo alla fine di una lista concatenata.
Riceve due parametri:
- lst: un doppio puntatore al primo nodo della lista
		(cioè un puntatore alla testa della lista).
- new: il nodo da aggiungere alla fine della lista.

Funzionamento della funzione:
1. Controlla se lst o new sono NULL.
	Se uno dei due è NULL, esce senza fare nulla.
2. Se la lista è vuota (*lst == NULL),
	il nuovo nodo diventa la testa della lista.
3. Se la lista contiene almeno un nodo,
	la funzione scorre la lista fino all'ultimo nodo.
4. Una volta trovato l'ultimo nodo (il cui next è NULL),
	collega il nuovo nodo a questo ultimo nodo. */

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}
