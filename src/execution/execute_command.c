/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:04 by begiovan          #+#    #+#             */
/*   Updated: 2025/07/22 12:37:36 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** count_word_tokens - Counts TK_WORD tokens in the list.
** @tokens: Pointer to the head of the token list.
** - Iterates through the token list.
** - Increments a counter for each token of type TK_WORD.
** Used to determine the number of arguments needed for allocation
** in convert_tokens_to_args().
*/
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

/*
** convert_tokens_to_args - Builds an argument array from TK_WORD tokens.
** - Counts TK_WORD tokens using count_word_tokens().
** - Allocates a NULL-terminated array of strings of size (count + 1).
** - Iterates through the token list:
**     - For each TK_WORD token, duplicates its value and stores in args.
** - Sets the last element to NULL.
*/
char	**convert_tokens_to_args(t_token *tokens)
{
	int		count;
	char	**args;
	t_token	*curr;
	int		i;

	i = 0;
	count = count_word_tokens(tokens);
	args = malloc(sizeof(char *) * (count + 1));
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

/*DA SISTEMARE*/
int	execute_command(t_token *tokens, t_shell *shell)
{
	char	**args;
	int		status;
	t_cmd	*cmd_list;

	if (!tokens)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_status = 127;
		return (127);
	}
	if (check_for_pipes(tokens))
	{
		cmd_list = convert_tokens_to_cmd_list(tokens);
		if (!cmd_list)
			return (-1);
		status = execute_pipeline(cmd_list, shell);
		free_cmd_list(cmd_list);
		return (status);
	}
	else
	{
		args = convert_tokens_to_args(tokens);		
		if (!args || !args[0])
		{
			free_split(args);
			return (-1);
		}
		status = execute_command_type(args, shell);
		free_split(args);
		return (status);
	}
}

/*
** execute_command_type - Determines and executes command type.
** This function determines whether the command is builtin or external.
**
** Behavior:
** - If builtin, dispatches to handle_builtin().
** - Otherwise, resolves the executable path via find_command_path().
** - If not found, prints error and returns -1.
** - If found, runs it using execute_external_command().
*/
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
