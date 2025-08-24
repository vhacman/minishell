/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lexer_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:31:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:47:24 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** ft_trim_spaces
**
** This function removes leading and trailing spaces or tabs
** from a string.
** - If the input string is NULL, return NULL.
** - Find the first non-space/tab character (start index).
** - Find the last non-space/tab character (end index).
** - Use ft_substr() to copy the substring between start and end.
** - Return the trimmed string (allocated).
*/
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

/*
** create_token
**
** This function creates a new token with the given value and type.
** - Allocate memory for a new t_token structure.
** - If allocation fails, return NULL.
** - Set the token type and duplicate the string value.
** - If string duplication fails, free the token and return NULL.
** - Initialize the next pointer to NULL.
** - Return a pointer to the newly created token.
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
** append_line_to_input
**
** This helper function appends a new line of text to an existing
** input string.
** - First, join the current input with a newline character.
** - If joining fails, free both the input and the line, then
**   return NULL.
** - Replace the old input with the joined string.
** - Join the result with the new line.
** - If this join fails, free both and return NULL.
** - Free the old parts after each successful join.
** - Return the final concatenated string.
*/
static char	*append_line_to_input(char *complete_input, char *line)
{
	char	*temp;
	char	*result;

	temp = complete_input;
	result = ft_strjoin(temp, "\n");
	if (!result)
	{
		free_parts(temp, line, NULL);
		return (NULL);
	}
	free(temp);
	temp = result;
	result = ft_strjoin(temp, line);
	if (!result)
	{
		free_parts(temp, line, NULL);
		return (NULL);
	}
	free_parts(temp, line, NULL);
	return (result);
}

/*
** get_complete_input
**
** This function builds a complete input string, handling cases
** where quotes are left unclosed.
** - Start by duplicating the initial input.
** - While unclosed quotes exist in the current string:
**     * Prompt the user with "> " and read another line.
**     * If the user provides no line (NULL), stop reading.
**     * Append the new line to the current input string using
**       append_line_to_input().
**     * If appending fails, return NULL.
** - Return the final complete input string.
*/
char	*get_complete_input(char *initial_input)
{
	char	*line;
	char	*complete_input;

	complete_input = ft_strdup(initial_input);
	if (!complete_input)
		return (NULL);
	while (has_unclosed_quotes(complete_input))
	{
		line = readline("> ");
		if (!line)
			break ;
		complete_input = append_line_to_input(complete_input, line);
		if (!complete_input)
			return (NULL);
	}
	return (complete_input);
}
