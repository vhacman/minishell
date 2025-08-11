/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:20:18 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 12:24:28 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
