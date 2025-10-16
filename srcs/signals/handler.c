/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/09 00:41:48 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

static void	handle_sigint_interactive(int signum)
{
	(void)signum;
	if (g_signal.signal_code != 1)
	{
		g_signal.signal_code = SIGINT + SIG_OFFSET;
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	init_signals(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, handle_sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signals_heredoc(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	rl_done = 1;
	g_signal.end_heredoc = 1;
	g_signal.signal_code = SIG_OFFSET + SIGINT;
}

void	sigint_exec(int signum)
{
	(void)signum;
	g_signal.signal_code = SIGINT + SIG_OFFSET;
	write(STDERR_FILENO, "\n", 1);
}
