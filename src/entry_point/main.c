/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 21:49:01 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Entry point for the minishell program.
** Initializes shell state, sets up signal handlers, and starts prompt.
** Cleans up resources before exiting with the final status.
*/
int	main(void)
{
	t_shell	shell;

	shell.exit_status = 0;
	init_shell(&shell);
	shell.program_name = ft_strdup("minishell");
	signal(SIGINT, handle_prompt_signal);
	signal(SIGQUIT, SIG_IGN);
	start_colored_prompt(&shell);
	cleanup(&shell);
	return (0);
}
