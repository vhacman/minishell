/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:41:09 by begiovan          #+#    #+#             */
/*   Updated: 2025/08/22 12:53:36 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
