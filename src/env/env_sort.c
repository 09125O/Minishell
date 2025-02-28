#include "minishell.h"

static void	print_export_line(char *key, char *value)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(key, 1);
	if (value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

static t_env	*find_min_key(t_env *env, char *last_key)
{
	t_env	*current;
	t_env	*min_node;

	current = env;
	min_node = NULL;
	while (current)
	{
		if (!last_key || ft_strcmp(current->key, last_key) > 0)
		{
			if (!min_node || ft_strcmp(current->key, min_node->key) < 0)
				min_node = current;
		}
		current = current->next;
	}
	return (min_node);
}

void	env_sort_and_print(t_env *env)
{
	t_env	*current;
	char	*last_key;

	if (!env)
		return ;
	last_key = NULL;
	while (1)
	{
		current = find_min_key(env, last_key);
		if (!current)
			break ;
		print_export_line(current->key, current->value);
		last_key = current->key;
	}
}
