#include "minishell.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	g_signo = 0;

void	handle_signal(int signo)
{
	g_signo = signo;
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	signals_init(void)
{
	g_signo = 0;
	if (signals_set_state(SIGNAL_INTERACTIVE) == SIGNAL_ERROR)
	{
		ft_putstr_fd("minishell: error: failed to set signal handlers\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	signals_reset(void)
{
	g_signo = 0;
}
