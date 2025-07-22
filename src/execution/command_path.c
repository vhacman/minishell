/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:11 by begiovan          #+#    #+#             */
/*   Updated: 2025/07/22 10:45:18 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** search_in_default_paths - Looks for a command in default system paths.
**
** @command: Name of the command to locate (e.g., "ls", "echo").
**
** This function attempts to locate an executable by concatenating
** the command name with a set of predefined directories:
**   - "/bin/"
**   - "/usr/bin/"
**   - "/usr/local/bin/"
** - Iterates through each default path.
** - Concatenates the path with the command name using ft_strjoin().
** - If the resulting path is executable (via access with X_OK), returns it.
** - Frees each unsuccessful path and continues.
*/
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

/*
** find_command_path - Resolves the full path to an executable command.
**
** @command: Command name as given by the user.
**
** This function determines whether the given command is:
** - An absolute or relative path (contains '/')
**   - If so, checks its executability via access(X_OK).
**   - Returns a copy of the path if accessible, NULL otherwise.
** - A bare command name (no '/')
**   - Searches in predefined system paths via search_in_default_paths().
** Return:
** - A newly allocated string containing the valid path to the executable,
** Used to prepare arguments for execve().
*/

/*
trova il percorso eseguibile di un comando. se il comando contiene una
barra e' un percorso relativo o assoluto.
Se e' eseguibile, restituisce una copia del path. Altrimenti restituisce NULL.
Se non contiene / cerca il comando nei percorsi standard. 
tramite search_in_default_paths.
*/
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
