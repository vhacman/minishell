/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:09 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/24 12:14:35 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** expand_program_name
**
** This function expands the special variable "$0" with the
** program name.
** - Split the input string into:
**     * "before": part of the string before "$0".
**     * "after": part of the string after "$0".
** - Replace "$0" with shell->program_name.
** - Concatenate before + program_name + after.
** - Free temporary strings and return the result.
*/
char	*expand_program_name(char *input, int pos, t_shell *shell)
{
	char	*before;
	char	*after;
	char	*result;
	char	*joined;

	before = ft_substr(input, 0, pos);
	after = ft_strdup(input + pos + 2);
	joined = ft_strjoin(before, shell->program_name);
	result = ft_strjoin(joined, after);
	return (free_parts(before, after, joined), result);
}

/*
** create_expanded_string
**
** This helper function builds a new string from three parts:
** - "before" + "value" + "after".
** - Used when expanding environment variables or exit status.
** - Returns the newly allocated string, or NULL on failure.
*/
char	*create_expanded_string(char *before, char *value, char *after)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(before, value);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, after);
	return (free(temp), result);
}

/*
** expand_exit_status
**
** This function expands the special variable "$?" with the
** shell's last exit status.
** - Extract "before" (part of string before "$?").
** - Extract "after" (part of string after "$?").
** - Convert shell->exit_status into a string.
** - Build new string: before + exit_status + after.
** - Free temporary strings and return the result.
*/
char	*expand_exit_status(char *str, int start, t_shell *shell)
{
	char	*before;
	char	*after;
	char	*exit_status_str;
	char	*result;

	before = ft_substr(str, 0, start);
	if (!before)
		return (NULL);
	after = ft_strdup(str + start + 2);
	if (!after)
		return (free(before), NULL);
	exit_status_str = ft_itoa(shell->exit_status);
	if (!exit_status_str)
	{
		free_parts(before, after, NULL);
		return (NULL);
	}
	result = create_expanded_string(before, exit_status_str, after);
	return (free_parts(before, after, exit_status_str), result);
}

/*
** find_variable_end
**
** This function determines where a variable name ends in a
** string after a '$' sign.
** - If the variable is "$?", return its end immediately.
** - Otherwise, advance until encountering a non-alphanumeric
**   and non-underscore character.
** - Return the index where the variable ends.
*/
int	find_variable_end(char *str, int start)
{
	int	i;

	i = start + 1;
	if (str[i] == '?')
		return (i + 1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

/*
** get_variable_value
**
** This function retrieves the value of an environment variable.
** - Extract the variable name between start and end indexes.
** - Look for it in the shell's environment list:
**     * If found and non-empty, duplicate its value.
** - If not found, try to get it from the system environment
**   using getenv().
** - If still not found, return an empty string.
** - Free the temporary var_name before returning.
*/
char	*get_variable_value(char *str, int start, int end, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	t_env	*node;
	char	*sys;

	var_name = ft_substr(str, start + 1, end - start - 1);
	if (!var_name)
		return (NULL);
	node = find_env_node(shell->env, var_name);
	if (node && node->value && node->value[0] != '\0')
		var_value = ft_strdup(node->value);
	else
	{
		sys = getenv(var_name);
		if (sys)
			var_value = ft_strdup(sys);
		else
			var_value = ft_strdup("");
	}
	return (free(var_name), var_value);
}
