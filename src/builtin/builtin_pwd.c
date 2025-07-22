/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:19:16 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/15 09:20:20 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** handle_pwd - Implements the builtin `pwd` command.
**
** This function retrieves and prints the current working directory
** of the shell process.
**
** - Calls getcwd(NULL, 0) to dynamically allocate a buffer with the
**   absolute path of the current working directory.
** - If getcwd fails, the function calls exit_with_error().
** - On success, prints the path to STDOUT followed by a newline.
** - Frees the dynamically allocated buffer after printing.
*/
int	handle_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		exit_with_error("getcwd", NULL, 0, 1);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
