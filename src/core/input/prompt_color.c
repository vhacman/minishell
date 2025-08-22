/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:19 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/22 12:08:13 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
