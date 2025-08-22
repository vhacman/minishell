/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 14:48:34 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_trim_spaces(const char *str)
{
	int		start;
	int		end;
	char	*trimmed;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] == ' ' || str[start] == '\t')
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && (str[end] == ' ' || str[end] == '\t'))
		end--;
	trimmed = ft_substr(str, start, end - start + 1);
	return (trimmed);
}

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

char	*get_complete_input(char *initial_input)
{
	char	*line;
	char	*temp;
	char	*complete_input;

	complete_input = ft_strdup(initial_input);
	if (!complete_input)
		return (NULL);
	while (has_unclosed_quotes(complete_input))
	{
		line = readline("> ");
		if (!line)
			break ;
		temp = complete_input;
		complete_input = ft_strjoin(temp, "\n");
		free(temp);
		temp = complete_input;
		complete_input = ft_strjoin(temp, line);
		free(temp);
		free(line);
	}
	return (complete_input);
}
