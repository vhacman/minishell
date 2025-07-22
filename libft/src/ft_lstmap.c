/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:13:32 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/04 14:13:32 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*   ft_lstmap: Itera sulla lista 'lst' e applica la funzione 'f' al 
contenuto di ciascun nodo, creando una nuova lista con i valori
trasformati. Ogni nuovo nodo viene allocato dinamicamente e aggiunto
alla fine della nuova lista. Se l'allocazione di un nodo fallisce,
la funzione libera l'intera nuova lista con 'del' e restituisce NULL.
Non modifica la lista originale e gestisce eventuali errori di memoria.*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		new_node = malloc(sizeof(t_list));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node->content = new_content;
		new_node->next = NULL;
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
