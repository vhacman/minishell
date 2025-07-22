/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:12:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/04 13:12:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//function that creates a newnode
// si definisce un puntatore a new_node ovvero il nuovo nodo della lista
//Il campo content del nuovo nodo viene impostato con il valore passato 
//come parametro alla funzione.
//Viene impostato il puntatore al nodo successivo --> new_node->next = NULL
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
