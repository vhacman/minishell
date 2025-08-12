/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:45:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 16:43:41 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Counts the number of path segments in a PATH string.
**
** Steps:
** 1. Initialize `count` to 1 (at least one segment exists).
** 2. Loop through each character in `path_env`.
** 3. Increment `count` every time ':' is found.
** 4. Return the total number of segments.
*/
int	count_path_segments(char *path_env)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (path_env[i])
	{
		if (path_env[i] == ':')
			count++;
		i++;
	}
	return (count);
}

/*
** Allocates memory for an array of path strings.
**
** Steps:
** 1. Use `calloc` to allocate and zero-initialize memory for
**    `count + 1` pointers to `char`.
**    - The extra slot is reserved for a NULL terminator.
** 2. Return the allocated array pointer.
*/
char	**allocate_paths_array(int count)
{
	char	**paths;

	paths = calloc(count + 1, sizeof(char *));
	return (paths);
}

/*
** Extracts a substring representing a single PATH segment.
**
** Steps:
** 1. Allocate `len + 1` bytes with `calloc` for the segment
**    plus the null terminator.
**    - If allocation fails, return NULL.
** 2. Copy `len` characters from `path_env` starting at
**    `start` into `segment` using `ft_strncpy`.
** 3. Return the allocated `segment`.
*/
char	*extract_path_segment(char *path_env, int start, int len)
{
	char	*segment;

	segment = calloc(len + 1, sizeof(char));
	if (!segment)
		return (NULL);
	ft_strncpy(segment, &path_env[start], len);
	return (segment);
}
