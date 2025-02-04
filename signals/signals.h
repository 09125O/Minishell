/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:05:36 by obouhour          #+#    #+#             */
/*   Updated: 2025/02/04 17:08:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
#define SIGNALS_H

#include "../env/env.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../exec/executor.h"
#include "../env/env.h"
#include "../utils/utils.h"

/*Vriable globale a deplacer dans le main.h*/
extern pid_t	global_pid;//a voir comment definir cette merde j'ai rien capte

//Configuration
void	configure_signals(void);
void	sigquit_handler(int sig);
void	sigint_handler(int sig);
void	eof_handler(void);
void	default_signals_handlers(void);

//Gestion heredoc
void	handle_heredoc_signals(void);
void	handle_heredoc(char *delimiter);

#endif