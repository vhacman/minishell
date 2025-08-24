/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:36 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/24 12:05:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*
** handle_pipeline_execution
**
** This function manages the execution of a full pipeline.
** - Convert the token list into a command list using
**   convert_tokens_to_cmd_list().
** - If conversion fails, return -1.
** - Call execute_pipeline() to run the commands.
** - Store the resulting status in shell->exit_status.
** - Return the final status.
*/
int	handle_pipeline_execution(t_token *tokens, t_shell *shell)
{
	int	status;

	shell->cmds = convert_tokens_to_cmd_list(tokens, shell);
	if (!shell->cmds)
		return (-1);
	status = execute_pipeline(shell->cmds, shell);
	shell->exit_status = status;
	return (status);
}


/*
** create_pipe_and_setup
**
** This function creates a pipe and sets up signals for execution.
** - Call pipe() to create a pipe.
** - If pipe creation fails, return 1.
** - Otherwise, set signals for command execution with
**   setup_signals_executing().
** - Return 0 on success.
*/
int	create_pipe_and_setup(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (1);
	setup_signals_executing();
	return (0);
}

/*
** execute_cmd_in_pipe
**
** This function executes a single command in the context of a
** pipe.
** - If the command or its arguments are invalid, print an error
**   and return 1.
** - If the command is a builtin, call handle_builtin().
** - Otherwise, find the command path with find_command_path().
**     * If not found, print an error and return 127.
** - Call execute_external_command() with the resolved path.
** - Free the command path and exit with the command's status.
*/
int	execute_cmd_in_pipe(t_cmd *cmd, t_shell *shell)
{
	char	*cmd_path;
	int		status;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		print_error("minishell: command structure error");
		return (1);
	}
	if (is_builtin(cmd->args[0]))
		return (handle_builtin(cmd->args, shell));
	cmd_path = find_command_path(cmd->args[0], shell);
	if (!cmd_path)
		return (print_error(cmd->args[0]), 127);
	status = execute_external_command(cmd_path, cmd->args, shell);
	free(cmd_path);
	exit(status);
}

/*
** handle_pipe
**
** This function handles execution of two commands connected
** by a pipe.
** - If cmd1, cmd2, or shell is invalid, print error and return.
** - Create a pipe with create_pipe_and_setup().
** - Fork the first child with fork_first_child().
** - Fork the second child with fork_second_child().
** - If forking fails, return an error.
** - Close both ends of the pipe in the parent process.
** - Wait for both child processes to finish with waitpid().
** - Update exit_status using handle_signal_exit_status() on the
**   second child's status.
** - Restore interactive signal handling.
** - Return the final exit_status of the shell.
*/
int	handle_pipe(t_cmd *cmd1, t_cmd *cmd2, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (!cmd1 || !cmd2 || !shell)
		return (print_error("Error: pipe"));
	if (create_pipe_and_setup(pipe_fd) != 0)
		return (1);
	pid1 = fork_first_child(cmd1, shell, pipe_fd);
	if (pid1 == -1)
		return (-1);
	pid2 = fork_second_child(cmd2, shell, pipe_fd, pid1);
	if (pid2 == -1)
		return (1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	handle_signal_exit_status(status2, shell);
	setup_signals_interactive();
	return (shell->exit_status);
}
