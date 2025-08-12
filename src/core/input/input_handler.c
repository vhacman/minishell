/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:04:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:32:20 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Creates a new string with leading and trailing spaces or
** tabs removed.
** 1. If `str` is NULL, return NULL.
** 2. Set `start` to the index of the first non-space/non-tab
**    character from the beginning.
** 3. Set `end` to the index of the last non-space/non-tab
**    character from the end.
** 4. Use `ft_substr` to create a substring from `start` to
**    `end` (inclusive).
** 5. Return the allocated trimmed string.
*/
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

/*
** Handles specific edge cases for user input before normal parsing.
** 1. Initialize `ret` to 0 (no special case detected).
** 2. Create a trimmed copy of `input` by removing leading
**    and trailing spaces with `ft_trim_spaces`.
** 3. Check if the trimmed input equals `""` or `''`:
**    - If yes:
**      * Print an error message indicating "command not found".
**      * Set the shell's `exit_status` to 127.
**      * Set `ret` to 1 (special case handled).
** 4. Free the trimmed string.
** 5. Return `ret` to indicate whether a special case was found.
*/
int	handle_special_cases(char *input, t_shell *shell)
{
	char	*trimmed;
	int		ret;

	ret = 0;
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

/*
** Processes a list of tokens by validating and executing commands.
** 1. If `tokens` is NULL, return immediately (nothing to process).
** 2. If there is only one token and its type is `TK_WORD`:
**    - If the token value is an empty string:
**      * Print an error message for "command not found".
**      * Set `exit_status` to 127.
**      * Free the token list and return.
**    - If the token value contains only spaces:
**      * Free the token list and return without error.
** 3. Otherwise, execute the command(s) with `execute_command`
**    and store the returned exit status in the shell.
*/
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

/*
** Processes a single line of user input for parsing and execution.
**
** Steps:
** 1. If `input` is NULL or empty, return immediately.
** 2. Call `check_signal_received` to handle any pending signals.
** 3. Add the input line to the command history.
** 4. Parse the input into tokens with `parse_line_to_tokens`.
** 5. If no tokens are generated, handle special cases
**    (e.g., built-ins without arguments) and return.
** 6. Check pipe syntax with `check_syntax_pipes`:
**    - If syntax is invalid, set `exit_status` to 2,
**      free the token and command lists, and return.
** 7. Process the tokens into executable commands
**    with `process_tokens`.
** 8. Clean up per-command resources after execution.
*/
void	handle_input(char *input, t_shell *shell)
{
	if (!input || *input == '\0')
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
	cleanup_per_command(shell);
}
