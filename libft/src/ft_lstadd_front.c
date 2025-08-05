/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:19:42 by vhacman           #+#    #+#             */
/*   Updated: 2025/03/04 13:19:42 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*I check for null pointers. If either lst(the list pointer)
or new (the new node) is NULL, the function does nothing.
The new node's **next** pointer is set to the current
first node of the list.
*lst = new --> the head of the list (lst) is updated
to ***new*** making it the new first node.*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("[%d] -> ", lst->data);
		lst = lst->next;
	}
	printf("NULL\n");
}

int	main(void)
{
	t_list *head = ft_lstnew(2);
	head->next = ft_lstnew(3);
	head->next->next = ft_lstnew(4);
	printf("Lista prima di ft_lstadd_front:\n");
	print_list(head);
	t_list *new_node = ft_lstnew(1);
	ft_lstadd_front(&head, new_node);
	printf("Lista dopo ft_lstadd_front:\n");
	print_list(head);
	returb(0);
}*/
