/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 16:19:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
