/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:07 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/24 12:15:15 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** expand_environment_variable
**
** This function expands a standard environment variable inside
** a string.
** - Parameters:
**     * str   : the full input string containing the variable.
**     * start : index of the '$' character.
**     * end   : index where the variable name ends.
**     * shell : structure containing the environment list.
** - Retrieve the variable's value using get_variable_value().
** - Extract "before" (substring before '$') and "after"
**   (substring after the variable).
** - Build the expanded string: before + var_value + after.
** - Free temporary strings before returning.
** - Return the new expanded string, or NULL on failure.
*/
char	*expand_environment_variable(char *str, int start, int end,
									t_shell *shell)
{
	char	*var_value;
	char	*before;
	char	*after;
	char	*result;

	var_value = get_variable_value(str, start, end, shell);
	if (!var_value)
		return (NULL);
	before = ft_substr(str, 0, start);
	after = ft_strdup(str + end);
	if (!before || !after)
		return (free_parts(var_value, before, after), NULL);
	result = create_expanded_string(before, var_value, after);
	return (free_parts(var_value, before, after), result);
}

/*
** process_dollar_sign
**
** This helper function expands a variable starting with '$'.
** - If '$' is the last character, no expansion is done and the
**   original string is returned.
** - If the next char is '?', expand to the shell's last exit code.
** - If the next char is '0', expand to the program name.
** - If the next char is alphabetic or '_', expand it as an
**   environment variable. The variable end is found using
**   find_variable_end().
** - If expansion fails, return the original string unchanged.
** - If expansion succeeds, free the old input and return the
**   newly expanded string.
*/
static char	*process_dollar_sign(char *input, int pos, t_shell *shell)
{
	char	*expanded;

	expanded = NULL;
	if (input[pos + 1] == '\0')
		return (input);
	if (input[pos + 1] == '?')
		expanded = expand_exit_status(input, pos, shell);
	else if (input[pos + 1] == '0')
		expanded = expand_program_name(input, pos, shell);
	else if (ft_isalpha(input[pos + 1]) || input[pos + 1] == '_')
		expanded = expand_environment_variable(input, pos,
				find_variable_end(input, pos), shell);
	if (!expanded)
		return (input);
	return (free(input), expanded);
}

/*
** expand_variables
**
** This function expands environment variables in the input string.
** - If input is NULL, return NULL immediately.
** - Duplicate the input string into result to work on a copy.
** - Iterate through each character of result:
**     * If a '$' is found and followed by another character,
**       call process_dollar_sign() to handle variable expansion.
**     * If process_dollar_sign() returns a new string, replace
**       result with it and restart from the same position.
** - Continue until the full string has been checked.
** - Return the final expanded string, or NULL on failure.
*/
char	*expand_variables(char *input, t_shell *shell)
{
	char	*result;
	char	*temp;
	int		i;

	if (!input)
		return (NULL);
	result = ft_strdup(input);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1])
		{
			temp = process_dollar_sign(result, i, shell);
			if (temp != result)
			{
				result = temp;
				continue ;
			}
		}
		i++;
	}
	return (result);
}
