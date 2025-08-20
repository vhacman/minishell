/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:34:24 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:05:45 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	validate_redirect_syntax(t_token *curr)
{
	if (curr->next == NULL || curr->next->type != TK_WORD)
	{
		ft_putstr_fd("minishell: syntax error near redirection\n", 2);
		return (-1);
	}
	return (0);
}

int	validate_heredoc_redirections(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr != NULL)
	{
		if (curr->type == TK_HEREDOC)
		{
			if (curr->next == NULL || curr->next->type != TK_WORD)
			{
				ft_putstr_fd(
					"minishell: syntax error near redirection\n", 2);
				return (-1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

int	validate_in_redirections(t_token *tokens)
{
	t_token	*curr;
	int		test_fd;

	curr = tokens;
	while (curr != NULL)
	{
		if (curr->type == TK_IN)
		{
			if (curr->next == NULL || curr->next->type != TK_WORD)
			{
				ft_putstr_fd(
					"minishell: syntax error near redirection\n", 2);
				return (-1);
			}
			test_fd = open(curr->next->value, O_RDONLY);
			if (test_fd == -1)
			{
				perror("minishell");
				return (-1);
			}
			close(test_fd);
		}
		curr = curr->next;
	}
	return (0);
}

int	validate_input_redirections(t_token *tokens)
{
	if (validate_in_redirections(tokens) == -1)
		return (-1);
	if (validate_heredoc_redirections(tokens) == -1)
		return (-1);
	return (0);
}
