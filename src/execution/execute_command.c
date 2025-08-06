/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:04 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/06 14:43:59 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_word_tokens(t_token *tokens)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_WORD)
			count++;
		curr = curr->next;
	}
	return (count);
}

char	**convert_tokens_to_args(t_token *tokens)
{
	int		count;
	char	**args;
	t_token	*curr;
	int		i;

	i = 0;
	count = count_word_tokens(tokens);
	args = calloc(sizeof(char *), (count + 1));
	if (!args)
		return (NULL);
	curr = tokens;
	while (curr)
	{
		if (curr->type == TK_WORD)
			args[i++] = ft_strdup(curr->value);
		curr = curr->next;
	}
	args[i] = NULL;
	return (args);
}

int execute_command(t_token *tokens, t_shell *shell)
{
	char	**args;
	int		status;

	if (!tokens)
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->exit_status = 127;
		return (127);
	}
	if (check_for_pipes(tokens))
	{
		shell->cmds = convert_tokens_to_cmd_list(tokens, shell);
		if (!shell->cmds)
			return (-1);
		status = execute_pipeline(shell->cmds, shell);
		shell->exit_status = status;
		return (status);
	}
	args = convert_tokens_to_args(tokens);
	if (!args)
	{
		cleanup(shell, 1);
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->exit_status = 127;
		return (127);
	}
	if (!args[0])
	{
		free_args_array(args);
		cleanup(shell, 1);
		ft_putstr_fd("minishell: : command not found\n", 2);
		shell->exit_status = 127;
		return (127);
	}
	if (is_builtin(args[0]))
	{
		if (ft_strcmp(args[0], "exit") == 0)
		{
			status = handle_exit(shell, args);
			if (status == 0)
			{
				free_args_array(args);
				cleanup(shell, 1);
				exit(shell->exit_status);
			}
			else
			{
				shell->exit_status = status;
				free_args_array(args);
				cleanup(shell, 1);
				return (status);
			}
		}
		else
			status = handle_builtin(args, shell);
	}
	else
		status = execute_command_type(args, shell);
	free_args_array(args);
	cleanup(shell, 1);
	shell->exit_status = status;
	return (status);
}

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
