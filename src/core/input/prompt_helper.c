/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:49:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:32:39 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Retrieves the current working directory and formats it
** for display in the shell prompt.
** 1. Use `getcwd` to obtain the absolute current working
**    directory path. If it fails, return "minishell ".
** 2. Retrieve the HOME directory path from the environment.
** 3. If the current directory matches HOME exactly, return
**    "~ " to represent it.
** 4. Otherwise, find the last '/' in the path:
**    - If a directory name exists after it, use only that
**      name with a trailing space.
**    - If no name follows, return "root ".
** 5. Free the original `cwd` string before returning.
*/
char	*get_current_directory(void)
{
	char	*cwd;
	char	*home;
	char	*result;
	char	*last_slash;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("minishell "));
	home = getenv("HOME");
	if (home && ft_strlen(cwd) == ft_strlen(home)
		&& ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		return (free(cwd), ft_strdup("~ "));
	last_slash = ft_strrchr(cwd, '/');
	if (last_slash && last_slash[1])
		result = ft_strjoin(last_slash + 1, " ");
	else
		result = ft_strdup("root ");
	free(cwd);
	return (result);
}

/*
** Handles SIGINT (Ctrl+C) during the shell prompt.
** 1. Ignore the actual signal value (`sig`).
** 2. Print a newline to move to a fresh prompt line.
** 3. Notify Readline that a new line has started.
** 4. Clear the current input line buffer.
** 5. Redisplay the updated prompt.
** This ensures the prompt is cleanly reset after Ctrl+C.
*/
void	handle_prompt_signal(int sig)
{
	(void)sig;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
