/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:49:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 21:52:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Signal handler for SIGINT at the prompt.
** This function handles Ctrl+C (SIGINT)
** - Calls rl_on_new_line() to inform readline that a new prompt is needed.
** - Uses rl_replace_line("", 0) to clear the current input line.
** - Calls rl_redisplay() to draw a fresh prompt with an empty buffer.
** Redisplays the prompt for a fresh input line.
*/
void	handle_prompt_signal(int sig)
{
	(void)sig;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
** Allocate buffer for current directory using getcwd(NULL,0).
** If allocation fails, return default "minishell " string.
** Retrieve HOME from environment; if cwd exactly equals HOME,
** free cwd and return "~ " to denote the home directory.
** Locate last '/' in cwd; if there is a name after it, prefix it
** and append a space to form "dirname ". Otherwise, use "root ".
** Always free the cwd buffer before returning the result string.
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
