#include "minishell.h"
#include <unistd.h>
#include "env.h"
#include <stdio.h>

int	env_set_shell_name(t_env **env, const char *name)
{
	int	status;

	if (!env || !name)
		return (ENV_INVALID_VALUE);

	env_lock();
	status = env_add(env, "0", name);
	env_unlock();
	return (status);
}

int	env_set_shell_pid(t_env **env)
{
	char	pid_str[16];
	int		status;

	if (!env)
		return (ENV_INVALID_VALUE);

	env_lock();
	snprintf(pid_str, sizeof(pid_str), "%d", (int)getpid());
	status = env_add(env, "$", pid_str);
	env_unlock();
	return (status);
}

int	env_set_last_bg_pid(t_env **env, int pid)
{
	char	pid_str[16];
	int		status;

	if (!env)
		return (ENV_INVALID_VALUE);

	env_lock();
	snprintf(pid_str, sizeof(pid_str), "%d", pid);
	status = env_add(env, "!", pid_str);
	env_unlock();
	return (status);
}

char	*get_special_var(const char *var_name, t_shell_ctx *ctx)
{
	char	*value;

	ft_putstr_fd("DEBUG: get_special_var appelé avec var_name=", 2);
	if (var_name)
		ft_putstr_fd(var_name, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putstr_fd("\n", 2);

	if (!var_name || !*var_name)
		return (ft_strdup("$"));

	ft_putstr_fd("DEBUG: Vérification du contexte shell\n", 2);
	if (!ctx)
	{
		ft_putstr_fd("DEBUG: Contexte shell NULL\n", 2);
		return (ft_strdup(""));
	}

	ft_putstr_fd("DEBUG: Comparaison avec les variables spéciales connues\n", 2);
	if (ft_strcmp(var_name, "?") == 0)
	{
		ft_putstr_fd("DEBUG: Variable $? détectée, valeur=", 2);
		ft_putnbr_fd(ctx->last_status, 2);
		ft_putstr_fd("\n", 2);
		value = ft_itoa(ctx->last_status);
		return (value ? value : ft_strdup("0"));
	}
	else if (ft_strcmp(var_name, "0") == 0)
	{
		ft_putstr_fd("DEBUG: Variable $0 détectée\n", 2);
		return (ft_strdup("minishell"));
	}
	else if (ft_strcmp(var_name, "$") == 0)
	{
		ft_putstr_fd("DEBUG: Variable $$ détectée\n", 2);
		value = ft_itoa(ctx->shell_pid);
		return (value ? value : ft_strdup("0"));
	}

	ft_putstr_fd("DEBUG: Aucune variable spéciale correspondante\n", 2);
	return (NULL);
}

int	is_special_var(const char *var_name)
{
	return (var_name && (*var_name == '?' ||
			*var_name == '0' ||
			*var_name == '$' ||
			*var_name == '!'));
}

void	update_special_var(t_shell_ctx *ctx, const char *var_name, int value)
{
	if (!ctx || !var_name)
		return;

	if (ft_strcmp(var_name, "?") == 0)
		ctx->last_status = value;
}
