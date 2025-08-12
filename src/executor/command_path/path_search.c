/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:45:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 12:30:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*build_full_path(char *dir, char *command)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, command);
	free(temp);
	return (full_path);
}

static char	*search_command_in_paths(char **paths, char *command)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], command);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*search_in_path_dirs(char *command, t_shell *shell)
{
	char	*path_env;
	char	**paths;
	char	*result;

	path_env = get_env_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = split_path_env(path_env);
	if (!paths)
		return (NULL);
	result = search_command_in_paths(paths, command);
	free_paths(paths);
	return (result);
}

char	*find_command_path(char *command, t_shell *shell)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
	return (search_in_path_dirs(command, shell));
}
