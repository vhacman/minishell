/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:20:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:32:56 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** Changes the current working directory to a specified path.
** 1. Save the current working directory in `old_pwd` for
**    later updating of PWD/OLDPWD.
**    - If retrieval fails, return 1.
** 2. If `path` is "-", call `handle_cd_dash` to switch to
**    the previous directory.
** 3. If `path` is "~", call `handle_cd_home` to switch to
**    the HOME directory.
** 4. Otherwise, attempt to change to the specified `path`
**    using `chdir`:
**    - If it fails, print the system error message with
**      `perror` and return 1.
** 5. If the directory change is successful, update PWD and
**    OLDPWD with `update_pwd_vars`.
** 6. Return 0 on success.
*/
int	handle_cd_path(t_shell *shell, char *path)
{
	char	old_pwd[PATH_MAX];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (1);
	if (ft_strcmp(path, "-") == 0)
		return (handle_cd_dash(shell));
	if (ft_strcmp(path, "~") == 0)
		return (handle_cd_home(shell));
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	update_pwd_vars(shell, old_pwd);
	return (0);
}

/*
** Handles the `cd` built-in command.
** 1. If no argument is provided (`args[1]` is NULL), change
**    to the HOME directory via `handle_cd_home`.
** 2. If more than one argument is provided (`args[2]` not NULL),
**    print an error message "cd: too many arguments" and return 1.
** 3. Otherwise, attempt to change to the specified path
**    using `handle_cd_path`.
** 4. Return the result from the called function.
*/
int	handle_cd(char **args, t_shell *shell)
{
	if (args[1] == NULL)
		return (handle_cd_home(shell));
	if (args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (handle_cd_path(shell, args[1]));
}
