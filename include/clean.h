/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:38:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/11 13:32:27 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

# include "structures.h"

/* =============================== */
/*       CLEANUP FUNCTIONS         */
/* =============================== */
// void        cleanup(t_shell *shell, int full_cleanup);
void		free_args_array(char **array);
void		free_parts(char *a, char *b, char *c);
void	    free_env_node(t_env *node);
void	    free_token_list(t_token **token);
void	    free_env_list(t_env *env);
void		free_cmd_list(t_cmd **cmds);
void	    free_cmd(t_cmd *cmd);
void        free_paths(char **paths);
void        cleanup_per_command(t_shell *shell);
void        destroy_shell(t_shell *shell);

#endif
