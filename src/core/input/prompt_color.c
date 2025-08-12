/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:19 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/12 17:32:31 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Builds a dynamic, color-coded shell prompt string.
** 1. Retrieve the current working directory with
**    `get_current_directory`.
** 2. Calculate the total buffer size as the directory length
**    plus extra space for colors and symbols.
** 3. Allocate a zero-initialized buffer for the prompt.
**    - If allocation fails, free `dir` and return a default
**      "minishell$ " prompt.
** 4. Append the blue color code and the directory path.
** 5. Add a space after the directory.
** 6. Append the prompt color based on the last exit status:
**    - Red if `exit_status` is non-zero (error).
**    - Green if `exit_status` is zero (success).
** 7. Append the arrow symbol followed by a reset color code
**    and a space.
** 8. Free the directory string and return the final prompt.
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
** Executes a single prompt cycle for the shell.
** 1. Build the dynamic colored prompt string with
**    `create_colored_prompt`.
** 2. Display the prompt and read a line of input using
**    `readline`.
** 3. Free the allocated prompt string.
** 4. If `input` is NULL (e.g., Ctrl+D), print "exit",
**    clean up per-command resources, and return 1 to stop
**    the shell.
** 5. Handle special cases (e.g., built-ins without parsing)
**    via `handle_special_cases`:
**    - If it returns a negative value, free `input`,
**      and return 1 to exit.
** 6. Pass the input to `handle_input` for parsing and
**    execution.
** 7. Clean up per-command resources before the next cycle.
** 8. Return 0 to continue the prompt loop.
*/
static int	run_prompt_once(t_shell *shell)
{
	char	*input;
	char	*prompt_str;
	int		special;

	prompt_str = create_colored_prompt(shell);
	input = readline(prompt_str);
	free(prompt_str);
	if (!input)
	{
		ft_printf("exit\n");
		cleanup_per_command(shell);
		return (1);
	}
	special = handle_special_cases(input, shell);
	if (special < 0)
	{
		free(input);
		return (1);
	}
	handle_input(input, shell);
	cleanup_per_command(shell);
	return (0);
}

/*
** Starts the interactive shell prompt with signal handling.
** 1. Configure signal handlers for interactive mode.
** 2. Enter an infinite loop to repeatedly display and
**    process the prompt:
**    - Call `run_prompt_once` to handle one prompt cycle.
**    - If it returns a non-zero value, break the loop.
** 3. Return the shell's last exit status.
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
