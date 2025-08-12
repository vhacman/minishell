/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:52:35 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Allocates and initializes a new token structure.
**
** Process:
** 1. Allocate memory for a `t_token` structure and set all bytes to zero.
**    - Return NULL if allocation fails.
** 2. Assign the given `type` to the token.
** 3. Duplicate the given `value` string and store it in `token->value`.
**    - If duplication fails, free the token structure and return NULL.
** 4. Initialize `token->next` to NULL.
*/
t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
		return (free (token), NULL);
	token->next = NULL;
	return (token);
}

/*
** Extracts the content inside quotes from the given string.
** Process:
** 1. If the current character matches `quote_char`, skip it.
** 2. Mark the starting position of the quoted content.
** 3. Move forward until the matching `quote_char` is found or end of string.
** 4. Extract the substring between the quotes using `ft_substr`.
** 5. If closing quote exists, skip it.
** 6. Update `index` to the position after the closing quote.
**
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
