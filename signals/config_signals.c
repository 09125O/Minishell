/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:37:38 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/19 14:19:46 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	default_signals_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	configure_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler; //Sert juste a dire si le SIGINT est recu on le gere avec cette fonction
	sigemptyset(&sa.sa_mask); // On vide le masque pour ne pas empecher d'autre signaux (voir *1*)
	sa.sa_flags = SA_RESTART; // On restart mainteant (*2*)
	sigaction(SIGINT, &sa, NULL); //On applique mainteant cette configuration au signal SIGINT 

	sa.sa_handler = sigquit_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}

/*
*1*:
Un masque sont des une liste de signaux qui sont bloquer, hors ici on ne veut pas bloquer l'acces a
d'autre signaux comme d'autre SIGINT ou encore SIGQUIT
*/

/*
*2*:
Cela sert pour l'utilisation de Readline, cela permet la reprise des commade comme read ou write
*/