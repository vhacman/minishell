/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 19:12:36 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:10:53 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** process_heredoc_line
**
** This helper function processes a single line in a heredoc.
** - Expand environment variables inside the line with
**   expand_variables().
** - Write the expanded line followed by a newline into the pipe.
** - If write fails, print an error, free memory, and return -1.
** - Free the expanded line and return 0 on success.
*/
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


/*
** read_heredoc_lines
**
** This function continuously reads user input until the heredoc
** delimiter is reached.
** - Prompt the user with "> " using readline().
** - If EOF is reached before the delimiter, print a warning and
**   stop reading.
** - If the input matches the delimiter, stop reading and free
**   the line.
** - Otherwise, process the line with process_heredoc_line() and
**   write it to the pipe.
** - Return 0 on success, or -1 if a write/processing error occurs.
*/
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


/*
** create_heredoc_pipe
**
** This function creates a pipe and fills it with heredoc input.
** - Create a pipe with pipe_fd.
**     * On failure, print error and return -1.
** - Call read_heredoc_lines() to read input until the delimiter
**   is found and write lines into the pipe's write end.
** - Close the write end of the pipe.
** - If an error occurred, close the read end and return -1.
** - Otherwise, return the read end of the pipe (pipe_fd[0]) so
**   it can be used as input redirection.
*/
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
