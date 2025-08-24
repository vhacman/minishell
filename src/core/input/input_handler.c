/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:04:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:16:03 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** process_tokens
**
** This function processes a list of tokens and executes a command.
** - If no tokens are provided, the function returns immediately.
** - If there is only one token and it is a word:
**     * If the word is empty, print an error and set exit code 127.
**     * If the word contains only spaces, print it as an error and
**       set exit code 127.
** - Otherwise, call execute_command to run the command and store
**   its exit status in the shell structure.
*/
void	process_tokens(t_token *tokens, t_shell *shell)
{
	int	exit_status;

	if (!tokens)
		return ;
	if (!tokens->next && tokens->type == TK_WORD)
	{
		if (tokens->value[0] == '\0')
		{
			ft_putstr_fd(": command not found\n", 2);
			shell->exit_status = 127;
			return ;
		}
		else if (only_spaces(tokens->value))
		{
			ft_putstr_fd(tokens->value, 2);
			ft_putstr_fd(": command not found\n", 2);
			shell->exit_status = 127;
			return ;
		}
	}
	exit_status = execute_command(tokens, shell);
	shell->exit_status = exit_status;
}

/*
** handle_input
**
** This function manages the processing of a command line input.
** - If the input is empty, the function returns immediately.
** - It first checks if a signal was received and updates the shell.
** - The input is completed (e.g., handling multi-line cases).
** - If valid, the line is added to the command history.
** - The input is then parsed into tokens and stored in the shell.
** - If parsing fails, the function stops.
** - Syntax of pipes is verified; if invalid, set exit code 2 and
**   free tokens and commands.
** - If valid, process the tokens to execute the command(s).
** - After execution, free resources related to the command.
*/
void	handle_input(char *input, t_shell *shell)
{
	char	*complete_input;

	if (!input || *input == '\0')
		return ;
	check_signal_received(shell);
	complete_input = get_complete_input(input);
	if (!complete_input)
		return ;
	add_history(complete_input);
	shell->tokens = parse_line_to_tokens(complete_input, shell);
	if (complete_input != input)
		free(complete_input);
	if (!shell->tokens)
		return ;
	if (check_syntax_pipes(shell->tokens))
	{
		shell->exit_status = 2;
		cleanup_per_command(shell);
		return ;
	}
	process_tokens(shell->tokens, shell);
	cleanup_per_command(shell);
}
