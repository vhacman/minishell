/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:55:14 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:14:47 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	setup_sigpipe_handling(void)
{
	signal(SIGPIPE, SIG_IGN);
}

int	has_input_redirection(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_IN || curr->type == TK_HEREDOC)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	has_output_redirection(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_OUT || curr->type == TK_APPEND)
			return (1);
		curr = curr->next;
	}
	return (0);
}
