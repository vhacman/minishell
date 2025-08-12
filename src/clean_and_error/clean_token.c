/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:21:19 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 15:40:05 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Frees all nodes in a linked list of tokens.
**
** Steps:
** 1. Loop while the token pointer is not NULL.
** 2. Store the pointer to the next token in `tmp`.
** 3. Free the current token's `value` string.
** 4. Free the token structure itself.
** 5. Move the main pointer to the next token (`tmp`).
** This ensures the entire token list is properly freed.
*/
void	free_token_list(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->value);
		free(*token);
		*token = tmp;
	}
}
