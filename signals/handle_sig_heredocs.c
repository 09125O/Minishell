/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:28:21 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/20 17:31:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	printf("\nHeredoc interrompu. Retour au prompt.\n");// On force une sortie immédiate en fermant le programme heredoc, a Revoir
	exit(1);
}

void	configure_heredoc_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN; // Ignorer SIGQUIT
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}

void	configure_default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_heredoc(char *delimiter)
{
	char	*line;

	configure_heredoc_signals();
	printf("Entrez vos lignes (Ctrl+D pour terminer, '%s' pour arrêter) :\n", delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line) // EOF (Ctrl+D)
		{
			printf("here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			break;
		}
		if (ft_strcmp(line, delimiter) == 0) // Délimiteur rencontré
		{
			free(line);
			break;
		}
		free(line);
	}
	configure_default_signals();
}
