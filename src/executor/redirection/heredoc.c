/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:12:36 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/20 19:22:42 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	process_heredoc_line(int write_fd, char *line, t_shell *shell)
{
	char	*expanded_line;

	expanded_line = expand_variables(line, shell);
	if (!expanded_line)
		return (-1);
	if (write(write_fd, expanded_line, ft_strlen(expanded_line)) == -1
		|| write(write_fd, "\n", 1) == -1)
	{
		perror("minishell: write");
		free(expanded_line);
		return (-1);
	}
	free(expanded_line);
	return (0);
}

static int	read_heredoc_lines(int write_fd, char *delimiter, t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("warning: ", 2);
			ft_putstr_fd("here-document delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(write_fd, line, shell) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	create_heredoc_pipe(char *delimiter, t_shell *shell)
{
	int	pipe_fd[2];
	int	result;

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	result = read_heredoc_lines(pipe_fd[1], delimiter, shell);
	close(pipe_fd[1]);
	if (result == -1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}
