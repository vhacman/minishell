/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/06 17:33:49 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(void)
{
	t_shell	shell;

	shell.exit_status = 0;
	init_shell(&shell);
	shell.program_name = ft_strdup("minishell");
	signal(SIGINT, handle_prompt_signal);
	signal(SIGQUIT, SIG_IGN);
	start_colored_prompt(&shell);
	destroy_shell(&shell);
	return (0);
}
