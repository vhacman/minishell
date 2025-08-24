/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:11:59 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:11:38 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** handle_redirection_with_tokens
**
** This function processes all input and output redirections
** defined in a token list.
** - First, validate input redirections with
**   validate_input_redirections().
**     * If invalid, return -1.
** - Then, apply input redirections using
**   handle_input_redirection_with_tokens().
**     * If it fails, return -1.
** - Finally, apply output redirections using
**   handle_output_redirection_token().
**     * If it fails, return -1.
** - If all steps succeed, return 0.
*/
int	handle_redirection_with_tokens(t_token *tokens, t_shell *shell)
{
	if (validate_input_redirections(tokens) == -1)
		return (-1);
	if (handle_input_redirection_with_tokens(tokens, shell) == -1)
		return (-1);
	if (handle_output_redirection_token(tokens, shell) == -1)
		return (-1);
	return (0);
}
