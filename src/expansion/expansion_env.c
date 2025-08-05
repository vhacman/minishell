/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:07 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/05 18:02:40 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (!before)
		return (free(var_value), NULL);
	after = ft_strdup(str + end);
	if (!after)
		return (free_parts(var_value, before, NULL), NULL);
	result = create_expanded_string(before, var_value, after);
	free_parts(var_value, before, after);
	return (result);
}

static char	*process_dollar_sign(char *input, int pos, t_shell *shell)
{
	char	*expanded;
	int		end_pos;

	if (input[pos + 1] == '\0')
		return (input);
	if (input[pos + 1] == '?')
		expanded = expand_exit_status(input, pos, shell);
	else if (input[pos + 1] == '0')
		expanded = expand_program_name(input, pos, shell);
	else if (ft_isalpha(input[pos + 1]) || input[pos + 1] == '_')
	{
		end_pos = find_variable_end(input, pos);
		expanded = expand_environment_variable(input, pos, end_pos, shell);
	}
	else
		return (input);
	if (expanded)
		return (free(input), expanded);
	return (input);
}

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
