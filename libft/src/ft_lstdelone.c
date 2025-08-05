/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:53:12 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/04 13:53:12 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*serve per eliminare un singolo nodo di una lista
collegata, liberando la memoria associata als uo contenuto.
void(*del)(void*)-->è un puntatore a una funzione che viene
usata per eliminare il contenuto del nodo. */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
