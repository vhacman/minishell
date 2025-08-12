/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:07 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/12 17:19:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** Expands an environment variable inside `str` between `start` and `end`.
**
** Steps:
** 1. Get the variable's value with `get_variable_value`;
**    return NULL on failure.
** 2. Create `before` = str[0..start) and `after` = str[end..]; if either
**    allocation fails, free temporaries and return NULL.
** 3. Build the final string with 
**   `create_expanded_string(before, var_value, after)`.
** 4. Free all temporaries (`var_value`, `before`, `after`)
**    and return the result.
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
		return NULL;
	before = ft_substr(str, 0, start);
	after  = ft_strdup(str + end);
	if (!before || !after)
		return (free_parts(var_value, before, after), NULL);
	result = create_expanded_string(before, var_value, after);
	return (free_parts(var_value, before, after), result);
}


/*
** Expands the variable that starts at position `pos` in `input`.
**
** Steps:
** 1. If '$' is the last char, return the original string.
** 2. Check the next char:
**    - '?' → expand with `expand_exit_status`.
**    - '0' → expand with `expand_program_name`.
**    - [A-Za-z_] → expand with `expand_environment_variable`
**      using `find_variable_end` to get the name bounds.
** 3. If expansion failed (NULL), return the original string.
** 4. On success, free the old `input` and return the expanded string.
*/
static char	*process_dollar_sign(char *input, int pos, t_shell *shell)
{
	char	*expanded;
	
	expanded = NULL;
	if (input[pos + 1] == '\0')
		return input;
	if (input[pos + 1] == '?')
		expanded = expand_exit_status(input, pos, shell);
	else if (input[pos + 1] == '0')
		expanded = expand_program_name(input, pos, shell);
	else if (ft_isalpha(input[pos + 1]) || input[pos + 1] == '_')
		expanded = expand_environment_variable(input, pos,
							find_variable_end(input, pos), shell);
	if (!expanded)
		return input;
	return (free(input), expanded);
}

/*
** Expands all environment variables in the given string.
**
** Steps:
** 1. If `input` is NULL, return NULL immediately.
** 2. Duplicate `input` into `result` to avoid modifying
**    the original string.
**    - If duplication fails, return NULL.
** 3. Iterate through each character of `result`:
**    - If a '$' is found and it is not the last character,
**      process it with `process_dollar_sign`.
**    - If `process_dollar_sign` returns a new string
**      (different from the original pointer), replace
**      `result` with this new string and restart checking
**      from the same index.
** 4. Continue until all characters have been scanned.
** 5. Return the final expanded string.
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
