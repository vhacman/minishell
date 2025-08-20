/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:11:59 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:22:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
