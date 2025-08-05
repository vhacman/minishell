/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:05:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/04 14:05:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*La funzione ft_lstiter serve per iterare su una lista collegata (t_list)
e applicare una funzione f al contenuto di ciascun nodo.
Si usa quando vogliamo applicare un'operazione a tutti gli elementi della lista,
ad esempio stamparli, modificarli o eseguire un'operazione generica.*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
void print_content(void *content)
{
	printf("%s\n", (char *)content);
}

int main()
{
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));
	t_list *node3 = malloc(sizeof(t_list));

	node1->content = ft_strdup("Nodo 1");
	node1->next = node2;

	node2->content = ft_strdup("Nodo 2");
	node2->next = node3;

	node3->content = ft_strdup("Nodo 3");
	node3->next = NULL;

   ft_lstiter(node1, print_content);

	return 0;
}

*/