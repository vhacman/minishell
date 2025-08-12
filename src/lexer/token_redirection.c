/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:56:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 16:21:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_redir_type_and_length(char first, char second, int *length)
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

void	get_redir(const char *input, int *curr_pos, int *type,
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

void	handle_redirection_token(const char *input, int *curr_pos,
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
