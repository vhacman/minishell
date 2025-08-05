/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:56:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 18:01:39 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*process_quoted_content(const char *input, int *i, t_shell *shell)
{
	char	*quoted;
	char	*expanded;
	char	quote_type;

	if (!input[*i])
		return (NULL);
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
	free (quoted);
	return (1);
}

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

static void get_redir(const char *input, int *curr_pos, int *type,
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

void handle_redirection_token(const char *input, int *curr_pos,
							  t_token **tokens)
{
	int			type;
	char		*token_str;
	t_token		*new_tok;

	get_redir(input, curr_pos, &type, &token_str);
	new_tok = create_token(token_str, type);
	add_token_to_list(tokens, new_tok);
	free(token_str);
}
