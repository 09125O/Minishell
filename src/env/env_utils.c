#include "minishell.h"

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	env_is_valid_key(const char *key)
{
	int	i;

	if (!key || !*key)
		return (0);

	if (ft_strcmp(key, "?") == 0 ||
		ft_strcmp(key, "0") == 0 ||
		ft_strcmp(key, "$") == 0 ||
		ft_strcmp(key, "!") == 0)
		return (1);

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	char	*tmp;
	int		i;
	t_env	*current;

	if (!env)
		return (NULL);
	array = malloc(sizeof(char *) * (count_env_vars(env) + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		if (!tmp)
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
		array[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
