/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:05:36 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/19 14:19:25 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
#define SIGNALS_H

#include "../env/env.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

/*Vriable globale a deplacer dans le main.h*/
extern pid_t	global_pid;//a voir comment definir cette merde j'ai rien capter

//Configuration
void	configure_signals(void);
void	sigquit_handler(int sig);
void	sigint_handler(int sig);
void	eof_handler(void);
void	default_signals_handlers(void);

#endif