/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:26:52 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 19:24:17 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	parse_env_arg(char *arg, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		*key = ft_strdup(arg);
		*value = NULL;
		return (*key != NULL);
	}
	*key = ft_substr(arg, 0, equal_sign - arg);
	*value = ft_strdup(equal_sign + 1);
	return (*key != NULL && *value != NULL);
}

static void	handle_export_error(char *arg)
{
	print_error("export", arg, "not a valid identifier");
}

static int	add_env_var(t_shell *shell, char *arg)
{
	char	*key;
	char	*value;

	if (!parse_env_arg(arg, &key, &value))
		return (EXIT_FAILURE);
	if (!is_valid_identifier(key))
	{
		free(key);
		free(value);
		handle_export_error(arg);
		return (EXIT_FAILURE);
	}
	set_env_var(&shell->env, key, value);
	free(key);
	free(value);
	return (EXIT_SUCCESS);
}

int	ft_export(t_shell *shell, char **args)
{
	int	i;
	int	status;

	if (!args[1])
	{
		print_sorted_env(shell);
		return (EXIT_SUCCESS);
	}
	status = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (add_env_var(shell, args[i]) != EXIT_SUCCESS)
			status = EXIT_FAILURE;
		i++;
	}
	return (status);
}
