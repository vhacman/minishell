/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:16:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:32:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** Handles the `cd` command with no arguments, changing
** the directory to the user's HOME.
** 1. Store the current working directory in `old_pwd` for
**    later updating of PWD/OLDPWD.
**    - If retrieval fails, return 1.
** 2. Retrieve the "HOME" variable from the environment.
**    - If it is not set or empty, print an error and return 1.
** 3. Attempt to change the directory to the HOME path:
**    - If it fails, print the system error message and
**      return 1.
** 4. Update the PWD and OLDPWD variables with
**    `update_pwd_vars`.
** 5. Return 0 on success.
*/
int	handle_cd_home(t_shell *shell)
{
	char	*home;
	char	old_pwd[PATH_MAX];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (1);
	home = get_env_value(shell->env, "HOME");
	if (!home || home[0] == '\0')
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("cd");
		return (1);
	}
	update_pwd_vars(shell, old_pwd);
	return (0);
}

/*
** Handles the `cd -` command, which switches to the
** previous working directory.
**
** Steps:
** 1. Retrieve the value of "OLDPWD" from the environment.
**    - If it is not set or empty, print an error and return 1.
** 2. Get the current working directory into `old_pwd` for
**    later updating of PWD/OLDPWD.
**    - If retrieval fails, return 1.
** 3. Attempt to change the directory to `oldpwd`:
**    - If it fails, print the system error message and
**      return 1.
** 4. Print the new current directory (`oldpwd`) to stdout.
** 5. Update the PWD and OLDPWD variables using
**    `update_pwd_vars`.
** 6. Return 0 on success.
*/
int	handle_cd_dash(t_shell *shell)
{
	char	*oldpwd;
	char	old_pwd[PATH_MAX];

	oldpwd = get_env_value(shell->env, "OLDPWD");
	if (!oldpwd || oldpwd[0] == '\0')
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (1);
	if (chdir(oldpwd) != 0)
	{
		perror("cd");
		return (1);
	}
	ft_printf("%s\n", oldpwd);
	update_pwd_vars(shell, old_pwd);
	return (0);
}

/*
** Updates the PWD and OLDPWD environment variables after
** a directory change.
**
** Steps:
** 1. Retrieve the current working directory into `cwd`
**    using `getcwd`.
** 2. If successful:
**    - Update "OLDPWD" in the shell's environment with the
**      provided `old_pwd` value.
**    - Update "PWD" with the current directory (`cwd`).
** This ensures the shell environment reflects the most
** recent directory change.
*/
void	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env_value(&shell->env, "OLDPWD", old_pwd);
		set_env_value(&shell->env, "PWD", cwd);
	}
}
