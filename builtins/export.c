/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:02:54 by root              #+#    #+#             */
/*   Updated: 2025/02/10 12:58:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void print_sorted_env(t_env *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < env->size_vars)
	{
		j = 0;
		while (j < env->size_vars - 1)
		{
			if (ft_strcmp(env->vars[j], env->vars[j + 1]) > 0)
			{
				tmp = env->vars[j];
				env->vars[j] = env->vars[j + 1];
				env->vars[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < env->size_vars)
	{
		printf("declare -x %s\n", env->vars[i]);
		i++;
	}
}

int ft_export(char **args, t_env *env)
{
	int		i;
	int		status;
	char	*value;
	char	*key;

	if (!args || !env)
		return (1);
	if (!args[1])
	{
		print_sorted_env(env);
		return (0);
	}
	status = 0;
	i = 1;
	while (args[i])
	{
		key = ft_strdup(args[i]);
		if (!key)
			return (1);
		value = ft_strchr(key, '=');
		if (value)
		{
			*value = '\0';
			value++;
			if (update_env_variable(env, key, value) == -1)
			{
				ft_error("export", args[i], "not a valid identifier");
				status = 1;
			}
		}
		free(key);
		i++;
	}
	return (status);
}
