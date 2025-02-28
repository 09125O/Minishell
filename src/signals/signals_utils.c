#include "minishell.h"
#include "signals.h"
#include <signal.h>

void	signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	signals_is_interrupted(void)
{
	extern volatile sig_atomic_t	g_signo;

	return (g_signo == SIGINT);
}
