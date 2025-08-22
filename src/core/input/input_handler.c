/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:04:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 12:42:08 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
		free_token_list(&shell->tokens);
		free_cmd_list(&shell->cmds);
		return ;
	}
	process_tokens(shell->tokens, shell);
	cleanup_per_command(shell);
}
