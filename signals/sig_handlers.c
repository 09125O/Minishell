/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:28:21 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/19 14:19:52 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	eof_handler(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("exit\n");
		exit(0);
	}
}

/* SIGINT = Ctrl + c */
void	sigint_handler(int sig) //le sginal d'un sigint est 2
{
	(void)sig; //Une fois identification reussi, la variable ne sert plus a rien 

	if (isatty(STDIN_FILENO))	//
	{							//
		printf("\n");			// Cette partie sert a bien verif qu'est dans un terminal
		rl_on_new_line();		// Ensuite on remet a jour readline, on vide le buffer
		rl_replace_line("", 0);	// et on affiche la nouvelle ligne
		rl_redisplay();			//
	}							//
}
/* SIGINT = Ctrl + l */
void	sigquit_handler(int sig)
{
	(void)sig;

	if (isatty(STDIN_FILENO))//si on est dans le terminal
		printf("\r");
	else //Si par exemple c'est un script
	{
		signal(SIGQUIT, SIG_DFL); //Dans ce cas (a revoir) on remet le signal comme il etait initialement
		kill(global_pid, SIGQUIT); //Global pid est definir, La fonction ici renvoie le siganl une nouvelle fois
	}
}
