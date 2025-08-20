/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:51:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 18:43:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
