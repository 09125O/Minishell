/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/09 00:27:24 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/** ERROR EXPORT */
void	error_export(char *input_line)
{
	ft_putstr_fd(P_NAME, STDERR_FILENO);
	ft_putstr_fd(": export: ", STDERR_FILENO);
	ft_putstr_fd(input_line, STDERR_FILENO);
	ft_putstr_fd(" : Not a valid identifier\n", STDERR_FILENO);
}

/** EXPORT (with no options)
 * Handling casess:
 * 1. export
 * 2. export ENV_VARIABLE=VALUE (-> add env variable)
 * 3. export ENV_VARIABLE1=VALUE1 ENV_VARIABLE2=VALUE2 ENV_VARIABLE3=VALUE3
 *
 * - If no arg -> print env according to alphabetic order
 * - If there's arg
 */
int	ft_export(t_shell *content, t_arg *args)
{
	if (!args)
	{
		if (export_print_sorted_env(content->env) != 0)
			return (SUCCESS);
	}
	else
	{
		while (args)
		{
			if (add_envvar(args->value, &(content->env)) != 0)
				return (FAILURE);
			args = args->next;
		}
	}
	return (SUCCESS);
}

/** EXPORT_PRINT_SORTED_ENV
 * (1) Transform env list to env arrays
 * (2) Sort env arrays by alphabetic orders
 * (3) Print arrays (export USER="lin"), 'export' + 'VAR=VALUE'
 * (4) Free the original environment array
 * (5) Free the sorted array
 * @note tmp_value = ft_strchr(sorted[i], '=') + 1; -> +1 to get value after '='
 *
 */
int	export_print_sorted_env(t_env *env)
{
	char	**env_arrs;
	char	**sorted;

	env_arrs = env_format(env);
	if (!env_arrs)
		return (FAILURE);
	sorted = sort_env_arrs(env_arrs);
	if (!sorted)
		return (arrs_free(env_arrs), FAILURE);
	print_export_all(sorted);
	arrs_free(sorted);
	arrs_free(env_arrs);
	return (SUCCESS);
}
