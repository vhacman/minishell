/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:10:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 14:15:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structures.h"

/* ========================= 1) EXECUTOR ENTRY POINTS ======================= */
int			execute_command(t_token *tokens, t_shell *shell);
int			handle_pipeline_execution(t_token *tokens, t_shell *shell);

/* ========================= 2) COMMAND PREPARATION ========================= */
char		**prepare_cmd_args(t_token *tokens, t_shell *shell);
char		**convert_tokens_to_args(t_token *tokens);
char		**build_envp_from_list(t_env *env);
int			count_word_tokens(t_token *tokens);
int			handle_null_tokens(t_shell *shell);
t_cmd		*create_new_cmd(void);

/* ======================= 3) COMMAND RESOLUTION (PATH) ===================== */
char		*find_command_path(char *command, t_shell *shell);
char		**split_path_env(char *path_env);
char		*extract_path_segment(char *path_env, int start, int len);
char		**allocate_paths_array(int count);
int			count_path_segments(char *path_env);

/* ========================= 4) COMMAND EXECUTION =========================== */
int			execute_command_type(char **args, t_shell *shell);
int			execute_external_command(char *cmd_path, char **args,
				t_shell *shell);

/* ============================== 5) PIPELINE =============================== */
int			execute_pipeline(t_cmd *cmds, t_shell *shell);
int			handle_pipe(t_cmd *cmd1, t_cmd *cmd2, t_shell *shell);
int			execute_cmd_in_pipe(t_cmd *cmd, t_shell *shell);
void		execute_child_process(t_cmd *curr, int prev_fd, int *pipe_fd,
				t_shell *shell);
int			execute_single_command(t_cmd *curr, int prev_fd, int *pipe_fd,
				t_shell *shell);
int			setup_command_execution(t_cmd *curr, int prev_fd, int *pipe_fd,
				pid_t *pid);
int			create_pipe_and_setup(int pipe_fd[2]);
int			setup_child_pipe(int pipe_fd[2], int is_left);
int			fork_first_child(t_cmd *cmd1, t_shell *shell, int pipe_fd[2]);
int			fork_second_child(t_cmd *cmd2, t_shell *shell, int pipe_fd[2],
				pid_t pid1);
void		setup_child_io_and_signals(t_cmd *curr,
				int prev_fd, int *pipe_fd, t_shell *shell);
int			check_for_pipes(t_token *tokens);
int			check_syntax_pipes(t_token *tokens);

/* ========================= 6) BUILTIN COMMANDS ========================== */
/* ------------------------------ Dispatch --------------------------------- */
int			is_builtin(char *command);
int			handle_builtin(char **args, t_shell *shell);
int			handle_other_builtins(char **args, t_shell *shell);

/* -------------------------------- cd -------------------------------------- */
int			handle_cd(char **args, t_shell *shell);
int			handle_cd_home(t_shell *shell);
int			handle_cd_dash(t_shell *shell);
int			handle_cd_path(t_shell *shell, char *path);
void		update_pwd_vars(t_shell *shell, char *old_pwd);

/* ------------------------------- pwd -------------------------------------- */
int			handle_pwd(void);

/* ------------------------------- echo ------------------------------------- */
int			handle_echo(t_shell *shell, char **args);

/* ------------------------------- env -------------------------------------- */
int			handle_env(t_shell *shell, char **args);
t_env		*create_env_node(char *key, char *value, int exported);
t_env		*copy_env_entries(char **env_entries);
t_env		*find_env_node(t_env *env_list, char *key);
char		*get_env_value(t_env *env, const char *key);
int			update_env_node(t_env *node, char *new_value, int exported_flag);
int			add_env_node(t_env **env_list, t_env *new_node);
int			set_env_value(t_env **envp, const char *key, const char *value);
size_t		count_env_nodes(t_env *env);

/* ------------------------------ export ------------------------------------ */
int			handle_export(t_env **env_list, char **argv);
int			export_variable(t_env **env_listp, char **args);
void		print_export_sorted(t_env *env_list);
void		print_exported_recursive(t_env **arr, int size, int i);
void		selection_sort_env(t_env **arr, int size);
int			env_list_size(t_env *env);
char		*extract_key(char *str);
char		*extract_value(char *str);
int			is_valid_identifier(char *str);

/* ------------------------------ unset ------------------------------------- */
int			handle_unset(t_env **env_list, char **argv);
int			unset_variable(t_env **env_list, char **args);
int			remove_env_node(t_env **env_list_ptr, char *key);

/* ------------------------------- exit ------------------------------------- */
int			handle_exit(t_shell *shell, char **args);
int			execute_exit(char **args, t_shell *shell);
int			is_numeric(char *str);
int			check_atol_conversion(char *str);
int			skip_whitespace(const char *str);

/* ========================= 7) REDIRECTIONS / IO =========================== */
/* --------------------------- Setup & Restore ------------------------------ */
int			setup_redirection(t_token *tokens, char **args, t_shell *shell);
int			handle_redirection_with_tokens(t_token *tokens, t_shell *shell);
int			handle_input_redirection_with_tokens(t_token *tokens,
				t_shell *shell);
void		restore_redirection(t_shell *shell);
void		restore_input_redirection(t_shell *shell);

/* ---------------------------- Detection ----------------------------------- */
int			has_input_redirection(t_token *tokens);
int			has_output_redirection(t_token *tokens);

/* -------------------------- File Operations ------------------------------- */
int			open_file_by_type(char *filename, int token_type, t_shell *shell);
int			open_input_file(t_token *curr, t_shell *shell);
int			open_output_file(t_token *curr, char **filename);
int			open_regular_file(char *filename, int token_type);

/* ------------------------- Redirection Handling -------------------------- */
int			apply_input_redirection(int input_fd, t_shell *shell);
int			setup_output_redirection(int file_fd, t_shell *shell);
int			handle_single_input_redirect(t_token *curr, t_shell *shell,
				int *input_fd);
int			handle_output_redirection_token(t_token *tokens, t_shell *shell);
void		update_input_fd(int *input_fd, int new_input_fd);

/* ---------------------------- Heredoc ------------------------------------- */
int			create_heredoc_pipe(char *delimiter, t_shell *shell);

/* ================================ 8) SIGNALS ============================= */
void		signal_handler_interactive(int sig);
void		signal_handler_executing(int sig);
void		handle_prompt_signal(int sig);
void		setup_signal_action(int signal, void (*handler)(int), int flags);
void		setup_signals_interactive(void);
void		setup_signals_executing(void);
void		setup_signals_child(void);
void		setup_sigpipe_handling(void);
int			handle_signal_exit_status(int status, t_shell *shell);
int			check_signal_received(t_shell *shell);
void		print_signal_message(int signal_number, int status);

#endif
