/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:36:53 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** add_token_to_list
**
** This function adds a new token to the end of a token list.
** - If head or new_token is NULL, do nothing.
** - If the list is empty, set head to the new token.
** - Otherwise, iterate through the list until the last token.
** - Link the new token to the end of the list.
*/
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

/*
** get_last_token
**
** This function returns the last token in a linked list of tokens.
** - If the list is empty (head is NULL), return NULL.
** - Otherwise, iterate through the list until the last node
**   (where next is NULL).
** - Return a pointer to the last token found.
*/
t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

/*
** append_token
**
** This helper function appends a token to the end of a token list.
** - If src_token is NULL, return NULL immediately.
** - Reset src_token->next to NULL to avoid dangling links.
** - If the list is empty, set both head and tail to src_token.
** - Otherwise, link src_token after the current tail and update
**   the tail pointer to the new last token.
** - Return the appended token.
*/
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

/*
** create_token_sublist
**
** This function builds a new sublist of tokens from start to end.
** - Initialize new_list and new_tail as empty.
** - Iterate from start until reaching end (excluded).
** - For each token, append it to the new list using append_token().
** - If appending fails, free the new list and return NULL.
** - Stop if end is reached.
** - Return the head of the new sublist.
*/
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
