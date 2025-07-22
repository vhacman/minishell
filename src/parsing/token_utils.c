/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 22:43:27 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	Creates a new token with given value and type, initializing next to NULL.
**
**	How it works	Allocates memory for t_token; if malloc succeeds,
**					assigns value and type, sets next to NULL.
**	Params:			value	- string for token value (ownership transferred)
**					type	- integer constant representing token type
**	Returns:		pointer to new t_token or NULL if allocation fails
*/
t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

/*
**	Adds a new token to the end of the token list.
**
**	How it works		If list is empty, sets head to new_token;
**						otherwise traverses to last node and links new_token.
**	Params:		head		- pointer to the head of the token list
**				new_token	- token to append to the list
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
**	Traverses the token linked list and returns its last element.
**	Returns NULL if the list is empty.
**
**	How it works		Checks if head is NULL, returns NULL; otherwise
**						iterates through list by following
						head->next until last node.
**	Params:	head		- pointer to the first token in the list
**	Returns:			pointer to the last token or NULL if list is empty
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
**	Extracts quoted content from input string between specified quotes.
**
**	How it works		Initializes 'i' from *index, sets start to i+1,
**						loops until matching quote_char or end of string,
**						duplicates substring with ft_substr and stores in
**						'quoted',
**						advances i past closing quote and updates *index.
**	Params:	str			- input string to extract from
**			index		- pointer to parse index
**			quote_char	- character delimiting quoted segment
*/
char	*extract_quoted_content(const char *str, int *index, char quote_char)
{
	int		start;
	char	*quoted;
	int		i;

	i = *index;
	if (str[i] == quote_char)
		i++;
	start = i;
	while (str[i] && str[i] != quote_char)
		i++;
	quoted = ft_substr(str, start, i - start);
	if (!quoted)
		return (NULL);
	if (str[i] == quote_char)
		i++;
	*index = i;
	return (quoted);
}
