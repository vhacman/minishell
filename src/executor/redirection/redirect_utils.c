/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:55:14 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:03:55 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** setup_sigpipe_handling
**
** This function configures signal handling for SIGPIPE.
** - Set SIGPIPE to be ignored (SIG_IGN).
** - Prevents the process from being terminated when writing
**   to a closed pipe, which is useful in pipelines where
**   commands may exit early.
*/
void	setup_sigpipe_handling(void)
{
	signal(SIGPIPE, SIG_IGN);
}

/*
** has_input_redirection
**
** This function checks if a command contains any input
** redirection tokens.
** - Iterate through the token list.
** - If a token is of type TK_IN ('<') or TK_HEREDOC ('<<'),
**   return 1 (true).
** - If no input redirection is found, return 0 (false).
*/
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

/*
** has_output_redirection
**
** This function checks if a command contains any output
** redirection tokens.
** - Iterate through the token list.
** - If a token is of type TK_OUT ('>') or TK_APPEND ('>>'),
**   return 1 (true).
** - If no output redirection is found, return 0 (false).
*/
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
