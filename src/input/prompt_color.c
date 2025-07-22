/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:19 by begiovan          #+#    #+#             */
/*   Updated: 2025/07/21 14:18:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** create_colored_prompt - Builds a dynamic prompt with color and state.
**
** @shell: Pointer to the shell structure for status context.
**
** Format:
**   - <blue>dir_name</blue> <green/red>➤</reset>
**
** Behavior:
** - Gets the current directory name u*create_colored_prompt
**   (t_shell *shellsing get_current_directory().
** - Allocates a buffer to hold the colored prompt string.
** - Appends components using ft_strlcpy/ft_strlcat to avoid overflows.
** - Uses GREEN if shell->exit_status == 0, otherwise RED.
**
** Memory:
** - Returns a dynamically allocated string.
** - Returns "minishell$ " on allocation failure.
*/
static char	*create_colored_prompt(t_shell *shell)
{
	char	*dir;
	char	*prompt;
	int		total_len;

	dir = get_current_directory();
	total_len = ft_strlen(dir) + 40;
	prompt = malloc(total_len);
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

int	start_colored_prompt(t_shell *shell)
{
	char	*input;
	char	*prompt_str;

	setup_signals_interactive();
	while (1)
	{
		prompt_str = create_colored_prompt(shell);
		input = readline(prompt_str);
		free(prompt_str);
		if (!input)
		{
			ft_printf("exit\n");
			break ;
		}
		handle_input(input, shell);
		free(input);
	}
	return (shell->exit_status);
}
