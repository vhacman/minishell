/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:30:53 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/04 13:30:53 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Inizializza un contatore count a 0. Scorre la lista nodo per nodo
usando un ciclo while. Ogni volta che passa a un nuovo nodo, incrementa
il contatore. restituisce il numero totale di nodi raggiunto la fine della
lista.*/
int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
int	main(void)
{
	t_list	*head;

	*head = ft_lstnew(10);
	head->next = ft_lstnew(20);
	head->next->next = ft_lstnew(30);
	printf("La lista ha %d nodi.\n", ft_lstsize(head));
	return (0);
}*/