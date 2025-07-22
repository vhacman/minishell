/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:51:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 22:46:59 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
**	Process next token based on current input character.
**	Dispatches to quoted, redirection, pipe, or word handlers.
**
**	How it works	Reads character at context->input[*context->i];
**				if quote, calls handle_quoted_token;
**				if '<' or '>', calls handle_redirection_token;
**				if '|', creates TK_PIPE token and advances index;
**				else calls handle_word_token.
**	Params:		context->input	- full command string to parse
**			context->i	- pointer to current parse index
**			context->tokens	- pointer to head of the token list
**	Returns:	1 on success, 0 if quoted handling fails
*/
static int	process_next_token(t_token_context *context)
{
	char	c;
	int		i;

	i = *(context->i);
	c = context->input[i];
	if (c == '\'' || c == '"')
		return (handle_quoted_token(context));
	if (c == '<' || c == '>')
		handle_redirection_token(context->input, context->i, context->tokens);
	else if (c == '|')
	{
		add_token_to_list(context->tokens,
			create_token(ft_strdup("|"), TK_PIPE));
		(*(context->i))++;
	}
	else
		handle_word_token(context);
	return (1);
}

/*
**	Parses a command line string into a linked list of tokens.
**	Iteratively skips whitespace and processes each token type.
**
**	How it works		Initializes context fields (input, i, tokens, shell);
**				loops while skip_whitespace_and_check returns true;
**				sets context.had_whitespace based on skipped spaces;
**				calls process_next_token to handle each token;
**				resets had_whitespace after each iteration.
**	Params:		str		- command line string to tokenize
**			shell	- shell context for variable expansion and env
**	Returns:	Pointer to head of token list, or NULL on error
*/
t_token	*parse_line_to_tokens(const char *str, t_shell *shell)
{
	t_token_context	context;
	t_token			*tokens;
	int				i;
	int				had_whitespace;

	tokens = NULL;
	i = 0;
	had_whitespace = 1;
	context.input = str;
	context.i = &i;
	context.tokens = &tokens;
	context.shell = shell;
	while (skip_whitespace_and_check(str, &i, &had_whitespace))
	{
		context.had_whitespace = had_whitespace;
		if (!process_next_token(&context))
			return (free_token_list(tokens), NULL);
		had_whitespace = 0;
	}
	return (tokens);
}
