/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:04:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/21 14:21:07 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_trim_spaces(const char *str)
{
	int		start;
	int		end;
	char	*trimmed;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] == ' ' || str[start] == '\t')
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && (str[end] == ' ' || str[end] == '\t'))
		end--;
	trimmed = ft_substr(str, start, end - start + 1);
	return (trimmed);
}

void	handle_special_cases(char *input, t_shell *shell)
{
	char	*trimmed;

	trimmed = ft_trim_spaces(input);
	if ((ft_strncmp(trimmed, "\"\"", 3) == 0)
		|| (ft_strncmp(trimmed, "''", 3) == 0))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(trimmed, 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_status = 127;
		free(trimmed);
		return ;
	}
	free(trimmed);
}

/*
** process_tokens:
** Handles token processing logic after tokenization,
** including edge cases (empty word, only spaces).
** Executes the command if valid.
*/
static void	process_tokens(t_token *tokens, t_shell *shell)
{
	if (!tokens->next && tokens->type == TK_WORD)
	{
		if (tokens->value[0] == '\0')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(": command not found\n", 2);
			shell->exit_status = 127;
			free_token_list(tokens);
			return ;
		}
		else if (only_spaces(tokens->value))
		{
			free_token_list(tokens);
			return ;
		}
	}
	shell->exit_status = execute_command(tokens, shell);
	free_token_list(tokens);
}

/*
** handle_input:
** Receives raw user input from the prompt,
** adds it to history, parses it into tokens,
** handles special cases or processes tokens.
*/
void	handle_input(char *input, t_shell *shell)
{
	t_token	*tokens;

	if(!input || *input == '\0')
		return ;
	check_signal_received(shell);
	add_history(input);
	tokens = parse_line_to_tokens(input, shell);
	if (!tokens)
	{
		handle_special_cases(input, shell);
		return ;
	}
	 if (check_syntax_pipes(tokens))
     {
    	shell->exit_status = 2;
        free_token_list(tokens);
        return ;
     }
	process_tokens(tokens, shell);
}
