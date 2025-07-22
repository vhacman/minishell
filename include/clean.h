/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:38:20 by vhacman           #+#    #+#             */
/*   Updated: 2025/07/16 21:11:07 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

# include "structures.h"

/* =============================== */
/*       CLEANUP FUNCTIONS         */
/* =============================== */
void		cleanup(t_shell *shell);
void		free_token_list(t_token *token);
void		free_split(char **array);
void		free_parts(char *a, char *b, char *c);

#endif
