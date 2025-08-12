/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:51:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 15:46:51 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Determines the type of the next token in the input
** and processes it accordingly.
**
** Steps:
** 1. Read the current character at the parsing index.
** 2. If it is a single or double quote, process it as a
**    quoted token with `handle_quoted_token`.
** 3. If it is a '<' or '>', process it as a redirection
**    token using `handle_redirection_token`.
** 4. If it is a '|', create a pipe token:
**    - Duplicate the "|" string.
**    - Create a token with type TK_PIPE.
**    - Add it to the token list.
**    - Free the temporary string.
**    - Increment the parsing index.
** 5. Otherwise, treat it as a normal word token and
**    process it with `handle_word_token`.
** 6. Always return 1 to indicate processing success.
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
** Main loop for tokenizing the input string.
**
** Steps:
** 1. Continuously call `skip_whitespace_and_check` to move
**    past spaces and determine if whitespace was present.
** 2. Store the current whitespace status in
**    `context->had_whitespace`.
** 3. Call `process_next_token` to parse the next token:
**    - If parsing fails, return 0 to indicate an error.
** 4. Reset `*had_whitespace` to 0 after processing a token.
** 5. Continue until no more tokens can be parsed, then
**    return 1 for success.
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
** Parses an input line into a linked list of tokens.
**
** Steps:
** 1. Initialize variables:
**    - `tokens` starts as NULL (empty list).
**    - `i` is the current parsing index.
**    - `had_whitespace` is set to 1 to handle leading spaces.
** 2. Fill a `t_token_context` structure with:
**    - The input string.
**    - Pointer to the index variable.
**    - Pointer to the tokens list.
**    - Reference to the shell instance.
** 3. Call `run_tokenization_loop` to perform the actual
**    token parsing:
**    - If it returns false, free any partially created tokens
**      and return NULL.
** 4. Return the head of the token list on success.
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
