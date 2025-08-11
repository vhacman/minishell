/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:11 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/11 13:37:34 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char **split_path_env(char *path_env)
{
	char	**paths;
	int		count;
	int		i;
	int		start;
	int		j;

	if (!path_env)
		return (NULL);
	count = 1;
	i = 0;
	while (path_env[i])
	{
		if (path_env[i] == ':')
			count++;
		i++;
	}
	paths = malloc(sizeof(char *) * (count + 1));
	if (!paths)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (path_env[i])
	{
		if (path_env[i] == ':' || path_env[i + 1] == '\0')
		{
			int len = (path_env[i] == ':') ? i - start : i - start + 1;
			paths[j] = malloc(len + 1);
			if (!paths[j])
			{
				while (--j >= 0)
					free(paths[j]);
				free(paths);
				return (NULL);
			}
			ft_strncpy(paths[j], &path_env[start], len);
			paths[j][len] = '\0';
			j++;
			start = i + 1;
		}
		i++;
	}
	paths[j] = NULL;
	return (paths);
}

static char *search_in_path_dirs(char *command, t_shell *shell)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	path_env = get_env_value(shell->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = split_path_env(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
		{
			free_paths(paths);
			return (NULL);
		}
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (!full_path)
		{
			free_paths(paths);
			return (NULL);
		}
				if (access(full_path, X_OK) == 0)
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

char *find_command_path(char *command, t_shell *shell)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		return (NULL);
	}
		return (search_in_path_dirs(command, shell));
}
