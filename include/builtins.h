/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:11:29 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 21:10:38 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structures.h"

int			is_builtin(char *command);
int			handle_builtin(char **args, t_shell *shell);

/* =============================== */
/*         CD FUNCTIONS            */
/* =============================== */
int			handle_cd(char **args, t_shell *shell);
int			handle_cd_home(t_shell *shell);
int			handle_cd_dash(t_shell *shell);
int			handle_cd_path(t_shell *shell, char *path);
void		update_pwd_vars(t_shell *shell, char *old_pwd);

/* =============================== */
/*        PWD FUNCTIONS            */
/* =============================== */
int			handle_pwd(void);

/* =============================== */
/*        ENV FUNCTIONS            */
/* =============================== */
int			handle_env(t_shell *shell, char **args);
t_env		*create_env_node(char *key, char *value, int exported);
t_env		*copy_env_entries(char **env_entries);
t_env		*find_env_node(t_env *env_list, char *key);
int			update_env_node(t_env *node, char *new_value, int exported_flag);
int			add_env_node(t_env **env_list, t_env *new_node);

/* =============================== */
/*       ECHO FUNCTIONS            */
/* =============================== */
int			handle_echo(t_shell *shell, char **args);

/* =============================== */
/*      EXPORT FUNCTIONS           */
/* =============================== */
int			export_variable(t_env **env_listp, char **args);
int			handle_export(t_env **env_list, char **argv);
void		print_export_sorted(t_env *env_list);
int			env_list_size(t_env *env);
char		*extract_key(char *str);
char		*extract_value(char *str);
int			is_valid_identifier(char *str);
void		print_exported_recursive(t_env **arr, int size, int index);
void		selection_sort_env(t_env **arr, int size);

/* =============================== */
/*       EXIT FUNCTIONS            */
/* =============================== */
int			handle_exit(t_shell *shell, char **args);
int			is_numeric(char *str);
void		exit_non_numeric(t_shell *shell, char *arg, char **args);
void		exit_with_code(t_shell *shell, char *arg, char **args);
int			exit_too_many_args(t_shell *shell);
void		exit_default(t_shell *shell, char **args);

#endif
