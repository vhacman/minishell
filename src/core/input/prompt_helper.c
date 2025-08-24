/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:49:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 11:57:41 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** get_current_directory
**
** This function returns a string representing the current
** working directory, formatted for the prompt.
** - Use getcwd() to retrieve the current directory path.
**     * If it fails, return a default string "minishell ".
** - Check if the current directory is the same as $HOME:
**     * If so, return "~ " instead of the full path.
** - Otherwise, find the last '/' in the path:
**     * If a directory name exists after it, return that name
**       followed by a space.
**     * If not, return "root ".
** - Free the original cwd string before returning the result.
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
** handle_prompt_signal
**
** This signal handler manages interactive prompt behavior
** (e.g., when Ctrl+C is pressed).
** - Ignore the signal value with (void)sig.
** - Print a newline to move to the next line.
** - Tell readline that a new line has started.
** - Clear the current input line with rl_replace_line().
** - Redisplay the prompt using rl_redisplay().
*/
void	handle_prompt_signal(int sig)
{
	(void)sig;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
