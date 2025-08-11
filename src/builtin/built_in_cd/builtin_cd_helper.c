/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:20:13 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 12:03:01 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*ritorna ptr al value nella lista env, o null se non esiste*/
char	*get_env_value (t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
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
