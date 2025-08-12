/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:09 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/12 15:52:27 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Expands the `$0` variable to the shell's program name.
**
** Steps:
** 1. Extract the substring before `$0` into `before` using
**    `ft_substr`.
** 2. Extract the substring after `$0` into `after` using
**    `ft_strdup`.
** 3. Concatenate `before` with `shell->program_name` into
**    `joined` using `ft_strjoin`.
** 4. Concatenate `joined` with `after` to form the final
**    expanded result.
** 5. Free `before`, `after`, and `joined` since their
**    contents have been copied into the result.
** 6. Return the expanded string.
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
** Combines three string segments into a single new string.
**
** Steps:
** 1. Join `before` and `value` into a temporary string
**    using `ft_strjoin`.
**    - If allocation fails, return NULL.
** 2. Join the temporary string with `after` to form the
**    final result.
** 3. Free the temporary string since it is no longer needed.
** 4. Return the final concatenated string.
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
** Expands the `$?` variable to the shell's last exit status.
**
** Steps:
** 1. Extract the substring before `$?` into `before` using
**    `ft_substr`.
**    - If allocation fails, return NULL.
** 2. Extract the substring after `$?` into `after` using
**    `ft_strdup`.
**    - If allocation fails, free `before` and return NULL.
** 3. Convert the shell's `exit_status` to a string using
**    `ft_itoa`.
**    - If allocation fails, free `before` and `after`, then
**      return NULL.
** 4. Concatenate `before`, `exit_status_str`, and `after`
**    into a new string using `create_expanded_string`.
** 5. Free `exit_status_str` after use, since its contents
**    have been copied into the result.
** 6. Return the final expanded string.
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
		return (free_parts(before, after, NULL), NULL);
	result = create_expanded_string(before, exit_status_str, after);
	return (free(exit_status_str), result);
}

/*
** Finds the end index of a variable name starting at `$`.
**
** Steps:
** 1. Start from the character after `$`.
** 2. If the next character is '?', return the index after it
**    (special variable `$?`).
** 3. Otherwise, move forward while the character is
**    alphanumeric or an underscore.
** 4. Return the index of the first character that is not
**    part of the variable name.
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
** Retrieves the value of a variable from the shell's
** environment or the system environment.
**
** Steps:
** 1. Extract the variable name from `str` using `ft_substr`,
**    excluding the `$` prefix.
**    - If allocation fails, return NULL.
** 2. Search for the variable in the shell's environment
**    with `find_env_node`.
**    - If found and it has a non-empty value, duplicate
**      this value into `var_value`.
** 3. If not found in the shell's environment:
**    - Look for it in the system environment with `getenv`.
**    - If found, duplicate the value.
**    - If not found, use an empty string.
** 4. Free the temporary `var_name` before returning.
** 5. Return the duplicated variable value.
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
