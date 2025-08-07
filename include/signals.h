/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:41:15 by vhacman           #+#    #+#             */
/*   Updated: 2025/08/06 19:25:29 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "structures.h"

/* =============================== */
/*       SIGNAL HANDLERS           */
/* =============================== */
void		signal_handler_interactive(int sig);
void		signal_handler_executing(int sig);
void		handle_prompt_signal(int sig);

/* =============================== */
/*       SIGNAL SETUP              */
/* =============================== */
void		setup_signal_action(int signal, void (*handler)(int), int flags);
void		setup_signals_interactive(void);
void		setup_signals_executing(void);
void		setup_signals_child(void);

/* =============================== */
/*      SIGNAL PROCESSING          */
/* =============================== */
int			handle_signal_exit_status(int status, t_shell *shell);
int			check_signal_received(t_shell *shell);


void	print_signal_message(int signal_number, int status);

#endif
