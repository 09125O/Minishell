#include "minishell.h"
#include <unistd.h>

static int	update_oldpwd(t_env **env)
{
	char	*old_pwd;

	old_pwd = env_get(*env, "PWD");
	if (old_pwd)
	{
		if (env_add(env, "OLDPWD", old_pwd) != ENV_SUCCESS)
			return (0);
	}
	return (1);
}

static int	update_current_pwd(t_env **env)
{
	char	buffer[4096];

	if (!getcwd(buffer, sizeof(buffer)))
		return (0);
	if (env_add(env, "PWD", buffer) != ENV_SUCCESS)
		return (0);
	return (1);
}

int	env_update_pwd(t_env **env)
{
	env_lock();
	if (!update_oldpwd(env))
	{
		env_unlock();
		return (0);
	}
	if (!update_current_pwd(env))
	{
		env_unlock();
		return (0);
	}
	env_unlock();
	return (1);
}

int	env_set_status(t_env **env, int status)
{
	char	status_str[16];
	int		result;

	env_lock();
	snprintf(status_str, sizeof(status_str), "%d", status);
	result = env_add(env, "?", status_str);
	env_unlock();
	return (result);
}

char	*env_get_status(t_env *env)
{
	char	*status;

	status = env_get(env, "?");
	if (!status)
		return (ft_strdup("0"));
	return (ft_strdup(status));
}
