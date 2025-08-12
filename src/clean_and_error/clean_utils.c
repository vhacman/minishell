/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:36:01 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 15:36:14 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Frees a partially allocated array of strings after an error.
**
** Steps:
** 1. Initialize `i` to 0.
** 2. Loop until `i` reaches `count`:
**    - Free each allocated string at index `i`.
**    - Increment `i` after each free.
** 3. Free the array pointer itself.
** This version frees in forward order instead of backward.
*/
void	free_paths_on_error(char **paths, int count)
{
	int	i;
	
	i = 0;
	while (i < count)
		free(paths[i++]);
	free(paths);
}

/*
** Frees a NULL-terminated array of strings.
**
** Steps:
** 1. If `array` is NULL, return immediately.
** 2. Iterate through each element until NULL is found:
**    - Free the string.
**    - Set the pointer to NULL to avoid dangling pointers.
** 3. Free the array itself after all elements are freed.
*/
void	free_args_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

/*
** Frees up to three dynamically allocated strings.
**
** Steps:
** 1. If `a` is not NULL, free it.
** 2. If `b` is not NULL, free it.
** 3. If `c` is not NULL, free it.
** This utility prevents repetitive NULL checks
** before freeing multiple strings.
*/
void	free_parts(char *a, char *b, char *c)
{
	if (a)
		free(a);
	if (b)
		free(b);
	if (c)
		free(c);
}
