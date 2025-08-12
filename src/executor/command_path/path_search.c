/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:45:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:41:26 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Builds the full filesystem path for a command by
** combining a directory path with the command name.
**
** Steps:
** 1. Join `dir` with a "/" separator to create `temp`.
**    - If allocation fails, return NULL.
** 2. Join `temp` with `command` to form `full_path`.
** 3. Free `temp` since its content is now part of
**    `full_path`.
** 4. Return the newly constructed `full_path`.
*/
static char	*build_full_path(char *dir, char *command)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, command);
	return (free(temp), full_path);
}

/*
** Searches for an executable command in a list of directories.
**
** Steps:
** 1. Iterate through each directory in `paths`.
** 2. For each directory:
**    - Build the full path to the command using
**      `build_full_path`.
**    - If allocation fails, return NULL.
**    - If the constructed path is accessible and executable
**      (`access` with X_OK), return it immediately.
**    - Otherwise, free the constructed path and continue.
** 3. If the command is not found in any directory, return NULL.
*/
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

/*
** Searches for an executable command in the directories
** listed in the PATH environment variable.
**
** Steps:
** 1. Retrieve the value of "PATH" from the shell's
**    environment using `get_env_value`.
**    - If it is not set, return NULL.
** 2. Split the PATH string into an array of directory paths
**    using `split_path_env`.
**    - If splitting fails, return NULL.
** 3. Search for the command in each directory with
**    `search_command_in_paths`.
** 4. Free the allocated array of paths using `free_paths`.
** 5. Return the found command path or NULL if not found.
*/
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
	return (free_paths(paths), result);
}

/*
** Determines the full path of a command to execute.
**
** Steps:
** 1. Check if `command` contains a '/' character:
**    - If yes, treat it as a direct or relative path.
**      - If the path is accessible and executable
**        (`access` with X_OK), return a duplicate of it.
**      - Otherwise, return NULL (invalid path or no permission).
** 2. If no '/' is present, search for the command in the
**    directories listed in the PATH environment variable
**    using `search_in_path_dirs`.
** 3. Return the found command path or NULL if not found.
*/
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
