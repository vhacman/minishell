/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:45:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:41:16 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/* state[0] = i, state[1] = j */
/*
** Extracts one PATH segment if a ':' or string end is found.
**
** - path_env: Original PATH string.
** - paths: Output array of strings.
** - start: Start index of current segment.
** - state[0]: Current index in path_env.
** - state[1]: Current index in paths array.
**
** Allocates segment via extract_path_segment(). On failure,
** frees previous entries and returns -1. Returns 1 if a
** segment was extracted, 0 otherwise.
*/
static int	process_path_segment(char *path_env, char **paths,
								int start, int state[2])
{
	int	len;
	int	is_delim;
	int	is_end;

	is_delim = (path_env[state[0]] == ':');
	is_end = (path_env[state[0] + 1] == '\0');
	if (is_delim || is_end)
	{
		if (is_delim)
			len = state[0] - start;
		else
			len = state[0] - start + 1;
		paths[state[1]] = extract_path_segment(path_env, start, len);
		if (!paths[state[1]])
		{
			free_paths_on_error(paths, state[1]);
			return (-1);
		}
		state[1] += 1;
		return (1);
	}
	return (0);
}

/*
** Splits `path_env` into directories and stores them in `paths`.
**
** - path_env: PATH string with ':' as separator.
** - paths: Pre-allocated array for results.
**
** - state[0]: Current index while iterating through `path_env`.
** - state[1]: Current position in the `paths` array for storing
**             the next directory.
**
** Iterates over path_env, calling process_path_segment() to
** extract each directory. Updates `start` after ':' and stops
** on error (-1). Ends with NULL-terminated array.
**
** Returns 0 on success, -1 on error.
*/
static int	iterate_path_string(char *path_env, char **paths)
{
	int	state[2];
	int	start;
	int	result;

	state[0] = 0;
	state[1] = 0;
	start = 0;
	while (path_env[state[0]])
	{
		result = process_path_segment(path_env, paths, start, state);
		if (result == -1)
			return (-1);
		if (result == 1)
			start = state[0] + 1;
		state[0]++;
	}
	paths[state[1]] = NULL;
	return (0);
}

/*
** Parses the PATH environment variable and fills the `paths`
** array with its individual directory components.
** 1. If `path_env` is NULL or an empty string:
**    - Set the first element of `paths` to NULL.
**    - Return 0 to indicate no paths were filled.
** 2. Otherwise, call iterate_path_string() to:
**    - Split `path_env` by ':' delimiters.
**    - Store each directory into the `paths` array.
**    - Ensure the array is NULL-terminated.
**
** Return:
** - 0 if `path_env` is empty or on success with no error.
** - The return value of iterate_path_string() if splitting
**   is performed.
*/
static int	parse_and_fill_paths(char *path_env, char **paths)
{
	if (!path_env || !path_env[0])
	{
		paths[0] = NULL;
		return (0);
	}
	return (iterate_path_string(path_env, paths));
}

/*
** Splits the PATH environment variable into an array of
** directory paths.
**
** Steps:
** 1. If `path_env` is NULL, return NULL (no PATH available).
** 2. Count the number of path segments in `path_env` using
**    `count_path_segments`.
** 3. Allocate memory for the array of paths with
**    `allocate_paths_array`.
**    - If allocation fails, return NULL.
** 4. Parse the PATH string and fill the array using
**    `parse_and_fill_paths`.
**    - If parsing fails (returns -1), return NULL.
** 5. Return the populated array of directory paths.
*/
char	**split_path_env(char *path_env)
{
	char	**paths;
	int		count;

	if (!path_env)
		return (NULL);
	count = count_path_segments(path_env);
	paths = allocate_paths_array(count);
	if (!paths)
		return (NULL);
	if (parse_and_fill_paths(path_env, paths) == -1)
		return (NULL);
	return (paths);
}
