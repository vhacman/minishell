/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:58:08 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** init_shell
**
** This function initializes the shell structure with default
** values before starting the shell.
** - Set pointers (line, tokens, cmds, env, args, program_name)
**   to NULL.
** - Set exit_status to 0.
** - Copy environment variables from the system 'environ'
**   into the shell with copy_env_entries().
** - Initialize saved_stdout and saved_stdin to -1 to indicate
**   that no descriptors are saved yet.
** - Initialize redirect_type to 0.
*/
void	init_shell(t_shell *shell)
{
	extern char	**environ;

	shell->line = NULL;
	shell->tokens = NULL;
	shell->cmds = NULL;
	shell->env = NULL;
	shell->exit_status = 0;
	shell->env = copy_env_entries(environ);
	shell->args = NULL;
	shell->program_name = NULL;
	shell->saved_stdout = -1;
	shell->saved_stdin = -1;
	shell->redirect_type = 0;
}

/*
** main
**
** Entry point of the minishell program.
** - Declare a t_shell structure to hold shell state.
** - Initialize exit_status to 0.
** - Call init_shell() to set up default values and environment.
** - Store the program name as "minishell".
** - Set up signal handlers:
**     * SIGINT (Ctrl+C) → handled by handle_prompt_signal().
**     * SIGQUIT (Ctrl+\) → ignored.
** - Start the interactive prompt loop with start_colored_prompt().
** - After exiting the loop, call destroy_shell() to free
**   all resources.
** - Return 0 as the program's exit code.
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
	destroy_shell(&shell);
	return (0);
}
