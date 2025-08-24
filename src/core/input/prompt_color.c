/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:19 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/24 11:56:59 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** create_colored_prompt
**
** This helper function builds the colored shell prompt string.
** - Get the current working directory with get_current_directory().
** - Allocate memory for the prompt, adding extra space for colors
**   and symbols (40 extra chars).
** - If allocation fails, free dir and return a simple fallback
**   prompt "minishell$ ".
** - Copy the BLUE color code and append the directory path.
** - Add a space after the directory.
** - If the last exit_status is non-zero, append the RED color,
**   otherwise append the GREEN color.
** - Append the arrow symbol ("➤") and reset the color.
** - Free the directory string.
** - Return the final allocated prompt string.
*/
static char	*create_colored_prompt(t_shell *shell)
{
	char	*dir;
	char	*prompt;
	int		total_len;

	dir = get_current_directory();
	total_len = ft_strlen(dir) + 40;
	prompt = calloc(1, total_len);
	if (!prompt)
	{
		free(dir);
		return (ft_strdup("minishell$ "));
	}
	ft_strlcpy(prompt, BLUE, total_len);
	ft_strlcat(prompt, dir, total_len);
	ft_strlcat(prompt, " ", total_len);
	if (shell->exit_status != 0)
		ft_strlcat(prompt, RED, total_len);
	else
		ft_strlcat(prompt, GREEN, total_len);
	ft_strlcat(prompt, "➤" RESET " ", total_len);
	free(dir);
	return (prompt);
}

/*
** run_prompt_once
**
** This function runs one iteration of the interactive prompt.
** - Build the prompt string with create_colored_prompt().
** - Display it and read user input using readline().
** - Free the allocated prompt string after use.
** - If readline() returns NULL (EOF or Ctrl+D):
**     * Print "exit" to stdout.
**     * Clean up resources for the current command.
**     * Return 1 to signal shell termination.
** - Otherwise, pass the input to handle_input() to process it.
** - Clean up resources for the current command after execution.
** - Return 0 to continue running the shell.
*/
static int	run_prompt_once(t_shell *shell)
{
	char	*input;
	char	*prompt_str;

	prompt_str = create_colored_prompt(shell);
	input = readline(prompt_str);
	free(prompt_str);
	if (!input)
	{
		ft_printf("exit\n");
		cleanup_per_command(shell);
		return (1);
	}
	handle_input(input, shell);
	cleanup_per_command(shell);
	return (0);
}

/*
** start_colored_prompt
**
** This function starts the main interactive prompt loop.
** - First, configure the signal handlers for interactive mode
**   using setup_signals_interactive().
** - Enter an infinite loop:
**     * Call run_prompt_once() to display the prompt, read input,
**       and process one command cycle.
**     * If run_prompt_once() returns 1, break the loop (exit).
** - After the loop ends, return the shell's exit_status as the
**   program's exit code.
*/
int	start_colored_prompt(t_shell *shell)
{
	setup_signals_interactive();
	while (1)
	{
		if (run_prompt_once(shell))
			break ;
	}
	return (shell->exit_status);
}
