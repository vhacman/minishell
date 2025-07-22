/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:56:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 22:36:29 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	Extracts and processes quoted content from input string.
**	Handles variable expansion for double quotes.
**
**	How it works		Reads quote character at input[*i] and calls
**						extract_quoted_content to get content until matching
**						quote; if quote_type is '"', calls expand_variables
**						and frees original string.
**	Params:		input	- full command string to parse
**				i		- pointer to current parse index
**				shell	- shell context for variable expansion
**	Returns:	pointer to quoted (and expanded) string, or NULL on error
*/
static char	*process_quoted_content(const char *input, int *i, t_shell *shell)
{
	char	*quoted;
	char	*expanded;
	char	quote_type;

	quote_type = input[*i];
	quoted = extract_quoted_content(input, i, quote_type);
	if (!quoted)
		return (NULL);
	if (quote_type == '"')
	{
		expanded = expand_variables(quoted, shell);
		free(quoted);
		if (!expanded)
			return (NULL);
		quoted = expanded;
	}
	return (quoted);
}

/*
**		Processes quoted content and adds or merges a word token.
**		Extracts quoted string and handles merging with previous word.
**
**	How it works		Calls process_quoted_content to get quoted text;
**						if no whitespace before and last token is TK_WORD,
**						appends text to that token; otherwise creates a
**						new TK_WORD token with the quoted text.
**	Params:		context->input			- full command string to parse
**				context->i				- pointer to current parse index
**				context->had_whitespace	- flag indicating preceding whitespace
**				context->tokens			- pointer to head of the token list
*/
int	handle_quoted_token(t_token_context *context)
{
	char	*quoted;
	t_token	*last_token;
	char	*new_value;

	quoted = process_quoted_content(context->input, context->i, context->shell);
	if (!quoted)
		return (0);
	if (!context->had_whitespace)
	{
		last_token = get_last_token(*(context->tokens));
		if (last_token && last_token->type == TK_WORD)
		{
			new_value = ft_strjoin(last_token->value, quoted);
			free(last_token->value);
			free(quoted);
			if (!new_value)
				return (0);
			last_token->value = new_value;
			return (1);
		}
	}
	add_token_to_list(context->tokens, create_token(quoted, TK_WORD));
	return (1);
}

/*
**		Determines redirection operator type and sets its length.
**		Returns the corresponding redirection token type.
**
**	How it works		Checks first and second chars:
**						'<<' => TK_HEREDOC, '>>' => TK_APPEND,
**						'>'  => TK_OUT, else '<' => TK_IN.
**						Sets *length.
**	Params:	first	-	first operator character
**			second	-	second operator character
**			length	-	pointer to store operator length
*/
static int	get_redir_type_and_length(char first, char second, int *length)
{
	if (first == '<' && second == '<')
		return (*length = 2, TK_HEREDOC);
	else if (first == '>' && second == '>')
		return (*length = 2, TK_APPEND);
	else if (first == '>')
		return (*length = 1, TK_OUT);
	else
		return (*length = 1, TK_IN);
}

/*
**		Determines redirection operator type and duplicates token string.
**		Advances index past the operator based on its length.
**
** How it works:		Reads input[i] and input[i+1], calls
**						get_redir_type_and_length to get type & length,
**						then moves the index and uses ft_strdup for the token.
** Params:	input		-	the null‑terminated command string to scan
**			curr_pos	-	pointer to the index tracking current parse position
**			type		-	pointer to store the redirection token type
**			token_str	-	pointer to hold the duplicated operator string
*/
static void	get_redir(const char *input, int *curr_pos, int *type,
						char **token_str)
{
	char	first;
	char	second;
	int		length;

	first = input[*curr_pos];
	second = input[*curr_pos + 1];
	*type = get_redir_type_and_length(first, second, &length);
	*curr_pos += length;
	if (*type == TK_HEREDOC)
		*token_str = ft_strdup("<<");
	else if (*type == TK_APPEND)
		*token_str = ft_strdup(">>");
	else if (*type == TK_OUT)
		*token_str = ft_strdup(">");
	else
		*token_str = ft_strdup("<");
}

/*
**				Parses a redirection operator and its operand from the input
**				string, then creates and appends a corresponding token.
** Params:	input	-	the null‑terminated command string to scan
**			curr_pos	-	pointer to the index tracking current parse position
** 			tokens	-	pointer to the head of the token list to update
*/
void	handle_redirection_token(const char *input, int *curr_pos,
								t_token **tokens)
{
	int		type;
	char	*token_str;

	get_redir(input, curr_pos, &type, &token_str);
	add_token_to_list(tokens, create_token(token_str, type));
}
