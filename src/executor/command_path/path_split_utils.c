/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:45:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 12:19:28 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

char	**allocate_paths_array(int count)
{
	char	**paths;

	paths = malloc(sizeof(char *) * (count + 1));
	return (paths);
}

char	*extract_path_segment(char *path_env, int start, int len)
{
	char	*segment;

	segment = calloc(len + 1, sizeof(char));
	if (!segment)
		return (NULL);
	ft_strncpy(segment, &path_env[start], len);
	return (segment);
}
