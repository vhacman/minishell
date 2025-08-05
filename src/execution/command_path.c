/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:11 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/05 18:03:25 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*search_in_default_paths(char *command)
{
	char	*paths[4];
	char	*full_path;
	int		i;

	paths[0] = "/bin/";
	paths[1] = "/usr/bin/";
	paths[2] = "/usr/local/bin/";
	paths[3] = NULL;
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], command);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *command)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	return (search_in_default_paths(command));
}
