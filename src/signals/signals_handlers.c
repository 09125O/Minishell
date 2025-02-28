#include "minishell.h"
#include "signals.h"
#include <signal.h>
#include <readline/readline.h>  // Pour les fonctions readline

static void	init_sigaction(struct sigaction *sa)
{
	sa->sa_handler = handle_signal;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
}

static void	set_handler_by_state(struct sigaction *sa, int state)
{
	if (state == SIGNAL_INTERACTIVE)
	{
		// En mode interactif, utiliser les gestionnaires spécifiques
		// pour SIGINT et SIGQUIT définis dans signals.c
		sa->sa_handler = SIG_IGN;  // Sera remplacé par les gestionnaires spécifiques
	}
	else if (state == SIGNAL_CHILD)
		sa->sa_handler = SIG_DFL;
	else if (state == SIGNAL_HEREDOC)
		sa->sa_handler = handle_signal;
	else
		sa->sa_handler = SIG_IGN;
}

int	signals_set_state(int state)
{
	struct sigaction	sa;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	init_sigaction(&sa);
	set_handler_by_state(&sa, state);

	if (state == SIGNAL_INTERACTIVE)
	{
		// Configuration spécifique pour le mode interactif
		sa_int.sa_handler = handle_sigint;
		sa_int.sa_flags = SA_RESTART;
		sigemptyset(&sa_int.sa_mask);

		sa_quit.sa_handler = SIG_IGN;  // Toujours utiliser SIG_IGN pour SIGQUIT en mode interactif
		sa_quit.sa_flags = SA_RESTART;
		sigemptyset(&sa_quit.sa_mask);

		if (sigaction(SIGINT, &sa_int, NULL) == -1)
			return (SIGNAL_ERROR);
		if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
			return (SIGNAL_ERROR);
	}
	else if (state == SIGNAL_CHILD)
	{
		// Pour les processus enfants, rétablir le comportement par défaut
		sa.sa_handler = SIG_DFL;
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (SIGNAL_ERROR);
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			return (SIGNAL_ERROR);
	}
	else
	{
		// Pour les autres états, utiliser la configuration générique
		if (sigaction(SIGINT, &sa, NULL) == -1)
			return (SIGNAL_ERROR);
		if (sigaction(SIGQUIT, &sa, NULL) == -1)
			return (SIGNAL_ERROR);
	}

	return (SIGNAL_SUCCESS);
}
