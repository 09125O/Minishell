#include "minishell.h"

char	*get_env_key(const char *env_str)
{
	char	*key;
	int		i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (env_str[i] && env_str[i] != '=')
	{
		key[i] = env_str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_env_value(const char *env_str)
{
	char	*value;
	int		i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (!env_str[i])
		return (ft_strdup(""));
	i++;
	value = ft_strdup(env_str + i);
	return (value ? value : ft_strdup(""));
}
