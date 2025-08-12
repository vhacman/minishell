/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:46:13 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:33:32 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** Implements the `env` built-in command to display environment variables.
** 1. If an argument is provided after `env` (`args[1]` not NULL),
**    print "env: too many arguments" to stderr and return 1.
** 2. Start from the head of the shell's environment list.
** 3. For each node that has a non-NULL value:
**    - Print the key to stdout.
**    - Print '='.
**    - Print the value followed by a newline.
** 4. Continue until all variables are processed.
** 5. Return 0 to indicate success.
*/
int	handle_env(t_shell *shell, char **args)
{
	t_env	*env;

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
