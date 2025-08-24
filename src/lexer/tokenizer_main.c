/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:51:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:30:39 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** process_next_token
**
** This helper function processes the next token in the input.
** - Reads the current character at the index from context.
** - If it is a single or double quote, call handle_quoted_token().
** - If it is a redirection symbol ('<' or '>'), call
**   handle_redirection_token() to parse it.
** - If it is a pipe ('|'), create a pipe token and add it to
**   the token list, then advance the index.
** - Otherwise, handle_word_token() is called to process a word.
** - Always returns 1 to indicate the function finished its job.
*/
static int	process_next_token(t_token_context *context)
{
	char	c;
	char	*token_str;
	int		i;

	i = *(context->i);
	c = context->input[i];
	if (c == '\'' || c == '"')
		return (handle_quoted_token(context));
	if (c == '<' || c == '>')
		handle_redirection_token(context->input, context->i, context->tokens);
	else if (c == '|')
	{
		token_str = ft_strdup("|");
		add_token_to_list(context->tokens,
			create_token(token_str, TK_PIPE));
		free(token_str);
		(*(context->i))++;
	}
	else
		handle_word_token(context);
	return (1);
}

/*
** run_tokenization_loop
**
** This helper function performs the main tokenization loop.
** - It repeatedly skips whitespace and checks if more input is
**   available.
** - The had_whitespace flag is updated in the context to indicate
**   whether whitespace appeared before the next token.
** - For each iteration, process_next_token() is called to extract
**   and store the next token.
** - If token processing fails, return 0 to signal an error.
** - When all tokens are processed successfully, return 1.
*/
static int	run_tokenization_loop(t_token_context *context, int *had_whitespace)
{
	while (skip_whitespace_and_check(context->input,
			context->i, had_whitespace))
	{
		context->had_whitespace = *had_whitespace;
		if (!process_next_token(context))
			return (0);
		*had_whitespace = 0;
	}
	return (1);
}

/*
** parse_line_to_tokens
**
** This function parses a command line into a list of tokens.
** - It initializes a token context with the input string, index,
**   token list pointer, and shell reference.
** - The variable had_whitespace tracks if whitespace was found
**   before a token (used for correct parsing).
** - It calls run_tokenization_loop() to process the input and
**   generate tokens.
** - If tokenization fails, all allocated tokens are freed and
**   NULL is returned.
** - On success, return the head of the token list.
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
	if (!run_tokenization_loop(&context, &had_whitespace))
		return (free_token_list(&tokens), NULL);
	return (tokens);
}
