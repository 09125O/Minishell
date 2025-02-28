#include "minishell.h"
#include <signal.h>

static volatile sig_atomic_t	g_env_lock = 0;

void	env_lock(void)
{
	sigset_t	mask;
	sigset_t	old_mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sigprocmask(SIG_BLOCK, &mask, &old_mask);
	while (g_env_lock)
		;
	g_env_lock = 1;
}

void	env_unlock(void)
{
	sigset_t	mask;
	sigset_t	old_mask;

	g_env_lock = 0;
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sigprocmask(SIG_UNBLOCK, &mask, &old_mask);
}

static int	update_single_var(t_env **env, const char *env_str)
{
	char	*key;
	char	*value;
	int		status;

	key = get_env_key(env_str);
	if (!key)
		return (0);
	value = get_env_value(env_str);
	if (!value)
	{
		free(key);
		return (0);
	}
	status = env_add(env, key, value);
	free(key);
	free(value);
	return (status == ENV_SUCCESS);
}

int	env_update_from_child(t_env **env, char **child_env)
{
	int		i;

	env_lock();
	i = 0;
	while (child_env && child_env[i])
	{
		if (!update_single_var(env, child_env[i]))
		{
			env_unlock();
			return (0);
		}
		i++;
	}
	env_unlock();
	return (1);
}
