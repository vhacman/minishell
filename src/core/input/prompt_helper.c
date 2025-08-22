/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:49:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 11:51:56 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

void	handle_prompt_signal(int sig)
{
	(void)sig;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
