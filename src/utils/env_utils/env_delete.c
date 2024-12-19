/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:56:18 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 21:24:30 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_env_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

static int	unset_first_node(t_env **env, const char *key)
{
	t_env	*current;

	if (!ft_strncmp((*env)->key, key, ft_strlen(key) + 1))
	{
		current = *env;
		*env = (*env)->next;
		free_env_node(current);
		return (1);
	}
	return (0);
}

int	unset_env_var(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !key)
		return (0);
	if (unset_first_node(env, key))
		return (1);
	prev = *env;
	current = (*env)->next;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
		{
			prev->next = current->next;
			free_env_node(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free_env_node(current);
		current = next;
	}
}
