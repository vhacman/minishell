/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:04:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/05 18:10:00 by vhacman          ###   ########.fr       */
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

int  handle_special_cases(char *input, t_shell *shell)
{
    char *trimmed;
    int   ret;

    ret     = 0;
    trimmed = ft_trim_spaces(input);
    if ((ft_strncmp(trimmed, "\"\"", 3) == 0)
     || (ft_strncmp(trimmed, "''", 3) == 0))
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(trimmed, 2);
        ft_putstr_fd(": command not found\n", 2);
        shell->exit_status = 127;
        ret = 1;
    }
    free(trimmed);
    return (ret);
}

static void	process_tokens(t_token *tokens, t_shell *shell)
{
	int	exit_status;

	if (!tokens)
		return ;
	if (!tokens->next && tokens->type == TK_WORD)
	{
		if (tokens->value[0] == '\0')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(": command not found\n", 2);
			shell->exit_status = 127;
			free_token_list(&tokens);
			return ;
		}
		else if (only_spaces(tokens->value))
		{
			free_token_list(&tokens);
			return ;
		}
	}
	exit_status = execute_command(tokens, shell);
	shell->exit_status = exit_status;
}

void	handle_input(char *input, t_shell *shell)
{
	if(!input || *input == '\0')
		return ;
	check_signal_received(shell);
	add_history(input);
	shell->tokens = parse_line_to_tokens(input, shell);
	if (!shell->tokens)
	{
		handle_special_cases(input, shell);
		return ;
	}
	if (check_syntax_pipes(shell->tokens))
	{
		shell->exit_status = 2;
		free_token_list(&shell->tokens);
		free_cmd_list(&shell->cmds);
		return ;
	}
	process_tokens(shell->tokens, shell);
	cleanup(shell, 0);
}
