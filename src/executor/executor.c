/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:24:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/06 19:28:31 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_command_type(char **args, t_shell *shell)
{
	char	*command_path;
	int		status;

	if (is_builtin(args[0]))
		return (handle_builtin(args, shell));
	command_path = find_command_path(args[0]);
	if (!command_path)
	{
		ft_printf("%s command not found\n", args[0]);
		return (-1);
	}
	status = execute_external_command(command_path, args, shell);
	free(command_path);
	return (status);
}

static int handle_null_tokens(t_shell *shell)
{
	ft_putstr_fd("minishell: : command not found\n", 2);
	shell->exit_status = 127;
	return (127);
}

static int handle_pipeline_execution(t_token *tokens, t_shell *shell)
{
	int status;

	shell->cmds = convert_tokens_to_cmd_list(tokens, shell);
	if (!shell->cmds)
		return (-1);
	status = execute_pipeline(shell->cmds, shell);
	shell->exit_status = status;
	return (status);
}

static char **prepare_cmd_args(t_token *tokens, t_shell *shell)
{
	char **args;

	args = convert_tokens_to_args(tokens);
	if (!args)
	{
		cleanup_per_command(shell);
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->exit_status = 127;
		return (NULL);
	}
	if (!args[0])
	{
		free_args_array(args);
		cleanup_per_command(shell);
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->exit_status = 127;
		return (NULL);
	}
	return (args);
}

static int setup_redirection(t_token *tokens, char **args, t_shell *shell)
{
	if (handle_redirection_with_tokens(tokens, shell) == -1)
	{
		free_args_array(args);
		cleanup_per_command(shell);
		shell->exit_status = 1;
		return (-1);
	}
	return (0);
}

static int handle_exit_builtin(char **args, t_shell *shell)
{
	int status;

	status = handle_exit(shell, args);
	if (status == 0)
	{
		free_args_array(args);
		destroy_shell(shell);
		exit(shell->exit_status);
	}
	else
	{
		shell->exit_status = status;
		free_args_array(args);
		cleanup_per_command(shell);
		return (status);
	}
	return (0);
}

static int handle_other_builtins(char **args, t_shell *shell)
{
	int status;

	status = handle_builtin(args, shell);
	cleanup_per_command(shell);
	return (status);
}

static int handle_external_command(char **args, t_shell *shell)
{
	int status;

	status = execute_command_type(args, shell);
	cleanup_per_command(shell);
	return (status);
}

int execute_command(t_token *tokens, t_shell *shell)
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
			return (handle_exit_builtin(args, shell));
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
