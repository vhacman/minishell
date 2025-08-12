/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:16:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 13:12:46 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

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

void	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env_value(&shell->env, "OLDPWD", old_pwd);
		set_env_value(&shell->env, "PWD", cwd);
	}
}
