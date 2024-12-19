/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:54:45 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 19:24:02 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**array;
	int		size;
	int		i;

	size = 0;
	current = env;
	while (current && ++size)
		current = current->next;
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		array[i++] = current->key;
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

void	sort_env_vars(char **vars)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	while (vars[size])
		size++;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(vars[j], vars[j + 1]) > 0)
				swap_strings(&vars[j], &vars[j + 1]);
			j++;
		}
		i++;
	}
}

void	print_sorted_env(t_shell *shell)
{
	t_env	*current;
	char	**keys;
	int		i;

	keys = env_to_array(shell->env);
	if (!keys)
		return ;
	sort_env_vars(keys);
	i = 0;
	while (keys[i])
	{
		current = get_env_node(shell->env, keys[i]);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(keys[i], 1);
		if (current && current->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
	free(keys);
}
