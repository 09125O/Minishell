/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:19:01 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/16 23:48:50 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

/* signals.c */
void	setup_signal_handlers(void);
void	reset_signal_handlers(void);
void	ignore_signals(void);

/* signal_handlers.c */
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_heredoc_signals(int sig);
void	setup_heredoc_signals(void);
void	restore_prompt_signals(void);

#endif
