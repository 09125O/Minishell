/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:31:28 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 23:33:09 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

/* États des signaux */
# define SIGNAL_DEFAULT		0
# define SIGNAL_INTERACTIVE	1
# define SIGNAL_CHILD		2
# define SIGNAL_HEREDOC		3

/* Codes de retour */
# define SIGNAL_SUCCESS		0
# define SIGNAL_ERROR		1

/* Variable globale pour le suivi des signaux */
extern volatile sig_atomic_t	g_signo;

/* Fonctions principales */
void	setup_signals(void);
void	reset_signals_for_child(void);
int	signals_init(void);
void	signals_reset(void);
int		signals_set_state(int state);

/* Gestionnaires de signaux */
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

/* Fonctions utilitaires */
void	handle_signal(int signo);
void	signals_ignore(void);
void	signals_default(void);
int		signals_is_interrupted(void);

#endif
