/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:36:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/04 13:36:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*la funzione restituisce l'ultimo nodo di una lista concatenata
Se la lista è vuota restituisce NULL. Scorre la lista fino all'ultimo nodo
e lo restituisce*/

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
int main()
{
	t_list *head = ft_lstnew(10);
	head->next = ft_lstnew(20);
	head->next->next = ft_lstnew(30);

	t_list *last = ft_lstlast(head);
	if (last)
		printf("L'ultimo nodo contiene: %d\n", last->data); // Output: 30
	else
		printf("La lista è vuota.\n");

	return 0;
}*/
