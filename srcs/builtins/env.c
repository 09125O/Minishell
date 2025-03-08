/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 22:52:55 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/** ERROR ENV */
void	error_env(char *input_line)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(input_line, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

/** FT_ENV (with no options/args)
 * - If no argument -> print env (arrays of arrays)
 * - If there is argument
 * -> output: env: '[input line]': No such file or directory
 * (1) Check if args exists
 * (2) Check if env list exists
 * (3) Loop through all environment variables
 * (4) Only print if variable has a value
 */
int	ft_env(t_shell *content, t_arg *args)
{
	t_env	*env;

	env = content->env;
	if (args)
	{
		error_env(args->value);
		content->exit_code = CMD_NOT_FOUND;
	}
	if (!env)
		return (SUCCESS);
	while (env)
	{
		if (env->value)
			printf("%s\n", env->env_line);
		env = env->next;
	}
	return (SUCCESS);
}
