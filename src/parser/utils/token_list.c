/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 18:58:34 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

static t_token	*append_token(t_token **head, t_token **tail,
									t_token *src_token)
{
	if (!src_token)
		return (NULL);
	src_token->next = NULL;
	if (!*head)
	{
		*head = src_token;
		*tail = src_token;
	}
	else
	{
		(*tail)->next = src_token;
		*tail = src_token;
	}
	return (src_token);
}

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
		if (!append_token(&new_list, &new_tail, curr))
			return (free_token_list(&new_list), NULL);
		if (curr == end)
			break ;
		curr = curr->next;
	}
	return (new_list);
}
