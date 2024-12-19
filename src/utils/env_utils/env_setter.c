/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:53:12 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/16 23:57:11 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_env	*create_env_var(const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

static void	add_env_var(t_env **env, t_env *new)
{
	t_env	*current;

	if (!*env)
	{
		*env = new;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	set_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*node;
	char	*new_value;

	if (!key || !value || !env)
		return (0);
	node = get_env_node(*env, key);
	if (node)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return (0);
		free(node->value);
		node->value = new_value;
		return (1);
	}
	node = create_env_var(key, value);
	if (!node)
		return (0);
	add_env_var(env, node);
	return (1);
}
