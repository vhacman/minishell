/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:59:54 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/04 13:59:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*La funzione ft_lstclear ha lo scopo di eliminare e liberare ricorsivamente 
tutti i nodi di una lista collegata, a partire dal nodo iniziale passato come
argomento, e alla fine deve impostare il puntatore alla lista a NULL.
*temp --> puntatore che memorizza il nodo successivo. viene elimnato il nodo
corrente e si passa al nodo successivo.*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
