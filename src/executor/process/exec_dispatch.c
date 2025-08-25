/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/25 15:30:41 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** handle_external_command
**
** This function handles the execution of an external command.
** - Call execute_command_type() with the arguments and shell
**   to run the command and store its status.
** - Restore the standard I/O streams with restore_redirection()
**   in case they were modified.
** - Clean up per-command resources with cleanup_per_command().
** - Return the command's exit status.
*/
static int	handle_external_command(char **args, t_shell *shell)
{
	int	status;

	status = execute_command_type(args, shell);
	restore_redirection(shell);
	cleanup_per_command(shell);
	return (status);
}

/*
** execute_command_type
**
** This function determines how to execute a command based on
** its type.
** - If the command is a builtin, call handle_builtin() and
**   return its result.
** - Otherwise, resolve the full path with find_command_path().
**     * If the path is not found, print "command not found"
**       and return exit status 127.
** - If a valid path is found, call execute_external_command().
** - Free the command path and return the command's exit status.
*/
int	execute_command_type(char **args, t_shell *shell)
{
	char	*command_path;
	int		status;

	if (!args || !args[0])
		return (127);
	if (is_builtin(args[0]))
		return (handle_builtin(args, shell));
	command_path = find_command_path(args[0], shell);
	if (!command_path)
	{
		ft_printf("%s command not found\n", args[0]);
		return (127);
	}
	status = execute_external_command(command_path, args, shell);
	free(command_path);
	return (status);
}

int	prepare_command(t_token *tokens, t_shell *shell, char ***args)
{
	*args = NULL;
	if (!tokens)
		return (handle_null_tokens(shell));
	if (check_for_pipes(tokens))
		return (handle_pipeline_execution(tokens, shell));
	*args = prepare_cmd_args(tokens, shell);
	if (setup_redirection(tokens, *args, shell) == -1)
	{
		if (*args)
			free_args_array(*args);
		*args = NULL;
		shell->exit_status = 1;
		return (1);
	}
	if (!*args || !(*args)[0] || (*args)[0][0] == '\0')
	{
		restore_redirection(shell);
		cleanup_per_command(shell);
		if (*args)
		{
			free_args_array(*args);
			*args = NULL;
		}
		shell->exit_status = 0;
		return (0);
	}
	return (-1);
}

int	execute_command(t_token *tokens, t_shell *shell)
{
	char	**args;
	int		status;
	int		prep_result;

	args = NULL;
	prep_result = prepare_command(tokens, shell, &args);
	if (prep_result != -1)
		return (prep_result);
	if (!args || !args[0])
	{
		restore_redirection(shell);
		cleanup_per_command(shell);
		shell->exit_status = 127;
		return (127);
	}
	if (is_builtin(args[0]))
	{
		if (ft_strcmp(args[0], "exit") == 0)
		{
			status = execute_exit(args, shell);
			return (status);
		}
		else
			status = handle_other_builtins(args, shell);
	}
	else
		status = handle_external_command(args, shell);
	if (args)
		free_args_array(args);
	shell->exit_status = status;
	return (status);
}