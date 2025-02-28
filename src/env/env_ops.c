#include "minishell.h"
#include "env.h"
#include <stdlib.h>

t_env	*env_dup(t_env *env)
{
	t_env	*new_env;
	t_env	*current;
	int		status;

	new_env = NULL;
	current = env;
	while (current)
	{
		status = env_add(&new_env, current->key, current->value);
		if (status != ENV_SUCCESS)
		{
			env_free(new_env);
			return (NULL);
		}
		current = current->next;
	}
	return (new_env);
}

static void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static int	check_env_remove_params(t_env **env, const char *key)
{
	if (!env || !key)
		return (ENV_INVALID_KEY);
	if (!env_is_valid_key(key))
		return (ENV_INVALID_KEY);
	if (!*env)
		return (ENV_NOT_FOUND);
	return (ENV_SUCCESS);
}

int	env_remove(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;
	int		status;

	status = check_env_remove_params(env, key);
	if (status != ENV_SUCCESS)
		return (status);

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free_env_node(current);
			return (ENV_SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (ENV_NOT_FOUND);
}

static int	env_key_exists(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

static int	update_env_value(t_env *env, const char *key, const char *value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			if (!env->value)
				return (ENV_MALLOC_ERROR);
			return (ENV_SUCCESS);
		}
		env = env->next;
	}
	return (ENV_NOT_FOUND);
}

int	env_add(t_env **env, const char *key, const char *value)
{
	t_env	*new_node;
	t_env	*current;

	if (!key || !value)
		return (ENV_INVALID_KEY);
	if (!env_is_valid_key(key))
		return (ENV_INVALID_KEY);
	if (env_key_exists(*env, key))
		return (update_env_value(*env, key, value));
	new_node = create_env_node(key, value);
	if (!new_node)
		return (ENV_MALLOC_ERROR);
	if (!*env)
	{
		*env = new_node;
		return (ENV_SUCCESS);
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (ENV_SUCCESS);
}
