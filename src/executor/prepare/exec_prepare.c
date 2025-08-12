/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:01:11 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Handles the case when no valid command tokens are found.
** 1. Print an error message "command not found" to stderr.
** 2. Set shell->exit_status to 127, the standard for command-not-found.
** 3. Return 127 to signal the error to the caller.
**
** Returns:
** - Always returns 127 (command not found).
*/
int	handle_null_tokens(t_shell *shell)
{
	ft_putstr_fd("minishell: : command not found\n", 2);
	shell->exit_status = 127;
	return (127);
}

/*
** Prepares the command arguments array excluding redirection tokens.
** Process:
** 1. Create args array without redirection tokens using
**    create_args_without_redirection().
** 2. If allocation fails or args[0] is NULL:
**    - Free args (if allocated).
**    - Perform per-command cleanup.
**    - Print "command not found" to stderr.
**    - Set shell->exit_status to 127.
**    - Return NULL to indicate failure.
** 3. On success, return the args array.
*/
char	**prepare_cmd_args(t_token *tokens, t_shell *shell)
{
	char	**args;

	args = create_args_without_redirection(tokens);
	if (!args)
	{
		cleanup_per_command(shell);
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->exit_status = 127;
		return (NULL);
	}
	if (!args[0])
	{
		free_args_array(args);
		cleanup_per_command(shell);
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->exit_status = 127;
		return (NULL);
	}
	return (args);
}

/*
** Sets up I/O redirections based on the provided token list.
** Process:
** 1. Call handle_redirection_with_tokens() to configure the I/O redirections.
** 2. If it fails (-1):
**    - Free the args array.
**    - Perform per-command cleanup.
**    - Set shell exit status to 1.
**    - Return -1 to indicate error.
** 3. If successful, return 0.
*/
int	setup_redirection(t_token *tokens, char **args, t_shell *shell)
{
	if (handle_redirection_with_tokens(tokens, shell) == -1)
	{
		free_args_array(args);
		cleanup_per_command(shell);
		shell->exit_status = 1;
		return (-1);
	}
	return (0);
}
