/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:07 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/22 12:52:30 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
