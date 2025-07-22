/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:46:13 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/15 10:40:49 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** handle_env - Implements the builtin `env` command.
**
** This function prints all environment variables stored in the shell's
** internal linked list. Each variable is printed only if it has a value,
** in the format: key=value\n
**
** - Iterates over the linked list `shell->env`.
** - For each node, if `value` is non-NULL, prints `key=value`.
** - Each entry is printed on a separate line to STDOUT.
*/
int	handle_env(t_shell *shell, char **args)
{
	t_env	*env;

	(void)args;
	if (args[1])
		return (ft_putstr_fd ("env: too many arguments", STDERR_FILENO), 1);
	env = shell->env;
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	return (0);
}
