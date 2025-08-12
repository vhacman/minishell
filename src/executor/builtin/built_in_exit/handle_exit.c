/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:58 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/12 17:33:59 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

/*
** Handles the `exit` command when an exit code argument is provided.
** 1. Validate the `exit_code`:
**    - If it is not numeric (`is_numeric` returns false) or
**      would overflow (`check_atol_conversion` returns true):
**        * Print "minishell: exit: <code>" followed by
**          "numeric argument required" to stderr.
**        * Set `exit_status` to 255.
**        * Free the arguments array and destroy the shell state.
**        * Exit the program with code 2.
** 2. If the exit code is valid, convert it to an integer with
**    `ft_atoi` and store it in `shell->exit_status`.
*/
static void	handle_exit_with_code(t_shell *shell, char **args, char *exit_code)
{
	if (!is_numeric(exit_code) || check_atol_conversion(exit_code))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putendl_fd(exit_code, STDERR_FILENO);
		ft_putendl_fd("numeric argument required", STDERR_FILENO);
		shell->exit_status = 255;
		free_args_array(args);
		destroy_shell(shell);
		exit(2);
	}
	else
		shell->exit_status = ft_atoi(exit_code);
}

/*
** Handles the `exit` built-in command and its arguments.
** 1. Count the number of arguments (`argc`).
** 2. If no additional arguments (`argc == 1`):
**    - Print "exit" to stdout.
**    - Set `exit_status` to 0 and return 0.
** 3. If exactly one argument (`argc == 2`):
**    - Call `handle_exit_with_code` to validate and set
**      the exit status based on the provided code.
**    - Return 0 to indicate the shell should exit.
** 4. If more than one argument:
**    - Print an error message indicating too many arguments.
**    - Set `exit_status` to 1 and return 1 (do not exit).
*/
int	handle_exit(t_shell *shell, char **args)
{
	int	argc;

	argc = 0;
	while (args[argc])
		argc++;
	if (argc == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		shell->exit_status = 0;
		return (0);
	}
	else if (argc == 2)
	{
		handle_exit_with_code(shell, args, args[1]);
		return (0);
	}
	else
	{
		ft_putendl_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
}
