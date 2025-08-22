/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:38:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/22 14:16:17 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

# include "structures.h"

/* ======================= 1) BASIC STRING & ARRAY CLEANUP ================== */
void		free_parts(char *a, char *b, char *c);
void		free_args_array(char **array);
void		free_paths(char **paths);
void		free_paths_on_error(char **paths, int j);

/* ======================== 2) TOKEN LIST CLEANUP =========================== */
void		free_token_list(t_token **token);

/* ======================= 3) ENVIRONMENT LIST CLEANUP ====================== */
void		free_env_node(t_env *node);
void		free_env_list(t_env *env);

/* ======================== 4) COMMAND LIST CLEANUP ========================= */
void		free_cmd(t_cmd *cmd);
void		free_cmd_list(t_cmd **cmds);

/* ====================== 5) SHELL LIFECYCLE MANAGEMENT ===================== */
void		cleanup_per_command(t_shell *shell);
void		destroy_shell(t_shell *shell);
void		cleanup_and_exit(t_cmd *curr, t_shell *shell, int exit_code);

#endif
