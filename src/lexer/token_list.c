/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:54:41 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Appends a new token to the end of a token list.
**
** Parameters:
** - head: Pointer to the head pointer of the token list.
** - new_token: Pointer to the token to be added.
**
** Process:
** 1. If `head` or `new_token` is NULL, do nothing.
** 2. If the list is empty (`*head` is NULL), set `*head` to `new_token`.
** 3. Otherwise, iterate to the last token in the list.
** 4. Set the last token's `next` pointer to `new_token`.
**
** This function ensures that tokens are stored in insertion order.
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
** Retrieves the last token in a token list.
**
** Parameters:
** - head: Pointer to the first token in the list.
**
** Process:
** 1. If the list is empty (`head` is NULL), return NULL.
** 2. Traverse the list until a token with `next` == NULL is found.
** 3. Return the pointer to this last token.
**
** Used when appending new tokens or accessing the list's tail.
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
** Appends a token to the end of a token list.
**
** Process:
** 1. If `src_token` is NULL, return NULL.
** 2. Set `src_token->next` to NULL to mark it as the new tail.
** 3. If the list is empty (`*head` is NULL), set both head and tail
**    to `src_token`.
** 4. Otherwise, link the current tail to `src_token` and update tail.
** 5. Return the appended token.
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
** Creates a sublist of tokens from `start` up to (but not including) `end`.
** Process:
** 1. Initialize an empty new list (`new_list`) and tail pointer (`new_tail`).
** 2. Iterate from `start` until reaching `end` or NULL.
** 3. Append each token to the new list using `append_token`.
**    - If appending fails, free the new list and return NULL.
** 4. Stop before `end` to exclude it from the sublist.
** 5. Return the new list's head pointer.
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
