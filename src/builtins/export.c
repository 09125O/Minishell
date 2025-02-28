/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:35:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 16:14:30 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	print_export_list(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("declare -x %s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
}

static char	*remove_quotes(char *str)
{
	int		len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') ||
		(str[0] == '\'' && str[len - 1] == '\'')))
	{
		result = ft_substr(str, 1, len - 2);
		free(str);
		return (result);
	}
	return (str);
}

static int	parse_env_var(char *arg, char **key, char **value)
{
	char	*equal_sign;
	char	*tmp_value;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		*key = ft_strdup(arg);
		*value = NULL;
		return (1);
	}
	*key = ft_substr(arg, 0, equal_sign - arg);
	tmp_value = ft_strdup(equal_sign + 1);
	*value = remove_quotes(tmp_value);
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		return (0);
	}
	return (1);
}

int	ft_export(char **args, t_env *env)
{
	char	*key;
	char	*value;
	int		i;
	int		ret;

	if (!args[1])
	{
		print_export_list(env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!parse_env_var(args[i], &key, &value))
		{
			ft_error("export", args[i], "invalid argument");
			ret = 1;
		}
		else if (!env_is_valid_key(key))
		{
			ft_error("export", args[i], "invalid identifier");
			ret = 1;
		}
		else if (value)
		{
			if (env_add(&env, key, value) != ENV_SUCCESS)
				ret = 1;
		}
		free(key);
		free(value);
		i++;
	}
	return (ret);
}
