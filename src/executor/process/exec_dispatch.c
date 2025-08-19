/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/19 12:38:49 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	handle_external_command(char **args, t_shell *shell)
{
	int	status;

	status = execute_command_type(args, shell);
	restore_redirection(shell);
	cleanup_per_command(shell);
	return (status);
}

int	execute_command_type(char **args, t_shell *shell)
{
	char	*command_path;
	int		status;

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

int	execute_command(t_token *tokens, t_shell *shell)
{
	char	**args;
	int		status;

	if (!tokens)
		return (handle_null_tokens(shell));
	if (check_for_pipes(tokens))
		return (handle_pipeline_execution(tokens, shell));
	args = prepare_cmd_args(tokens, shell);
	if (!args)
		return (127);
	if (setup_redirection(tokens, args, shell) == -1)
		return (1);
	if (is_builtin(args[0]))
	{
		if (ft_strcmp(args[0], "exit") == 0)
			return (execute_exit(args, shell));
		else
			status = handle_other_builtins(args, shell);
	}
	else
		status = handle_external_command(args, shell);
	free_args_array(args);
	cleanup_per_command(shell);
	shell->exit_status = status;
	return (status);
}
