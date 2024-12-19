/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:56:33 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/16 23:52:50 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_env	*get_env_node(t_env *env, const char *key)
{
	size_t	key_len;

	if (!key || !env)
		return (NULL);
	key_len = ft_strlen(key);
	while (env)
	{
		if (!ft_strncmp(env->key, key, key_len) && !env->key[key_len])
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_var(t_env *env, const char *key)
{
	t_env	*node;

	node = get_env_node(env, key);
	if (!node)
		return (NULL);
	return (node->value);
}

int	env_var_exists(t_env *env, const char *key)
{
	return (get_env_node(env, key) != NULL);
}
