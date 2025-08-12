/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:35:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:32:44 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Initializes all fields of the t_shell structure
** to prepare the shell for execution.
** 1. Set pointers (line, tokens, cmds, env, args,
**    program_name) to NULL to avoid undefined values.
** 2. Set numeric fields (exit_status, saved_stdout,
**    redirect_type) to default values.
** 3. Copy the current environment variables from
**    `environ` into the shell's own environment storage
**    using `copy_env_entries`.
** This ensures the shell starts in a clean, predictable
** state before processing user input.
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
	shell->redirect_type = 0;
}

/*
** Entry point of the minishell program.
** Initializes the shell structure, sets default values,
** and prepares the shell environment before starting
** the interactive prompt loop.
** 1. Set the initial exit status to 0.
** 2. Initialize the shell structure with `init_shell`.
** 3. Store the program name for later reference.
** 4. Configure signal handlers:
**    - SIGINT is handled to control prompt interruption.
**    - SIGQUIT is ignored.
** 5. Launch the interactive prompt with color support.
** 6. Free all allocated resources before exiting.
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
