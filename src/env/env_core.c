#include "minishell.h"

t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*new_node;

	if (!key || !value)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

static int	process_env_var(t_env **env_list, const char *env_str)
{
	char	*key;
	char	*value;
	t_env	*new_node;

	if (!env_list || !env_str)
		return (0);
	key = get_env_key(env_str);
	if (!key)
		return (0);
	value = get_env_value(env_str);
	if (!value)
	{
		free(key);
		return (0);
	}
	new_node = create_env_node(key, value);
	free(key);
	free(value);
	if (!new_node)
		return (0);
	new_node->next = *env_list;
	*env_list = new_node;
	return (1);
}

t_env	*env_init(char **envp)
{
	t_env	*env_list;
	int		i;

	if (!envp)
		return (NULL);
	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		if (!process_env_var(&env_list, envp[i]))
		{
			env_free(env_list);
			return (NULL);
		}
		i++;
	}
	return (env_list);
}

void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
