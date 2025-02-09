/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:02:54 by root              #+#    #+#             */
/*   Updated: 2025/02/09 17:06:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_sorted_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
		i++;
	while (i > 0)
	{
		j = 0;
		while (j < i - 1)
		{
			if (strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i--;
	}
	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

int	ft_export(char **args, char **env)
{
	int		i;
	int		status;
	char	*value;

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
		value = ft_strchr(args[i], '=');
		if (value)
		{
			*value = '\0';
			value++;
			if (ft_setenv(args[i], value, env) == -1)
			{
				ft_error("export", args[i], "not a valid identifier");
				status = 1;
			}
		}
		i++;
	}
	return (status);
}
