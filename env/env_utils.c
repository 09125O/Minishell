/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:52:00 by obouhour          #+#    #+#             */
/*   Updated: 2025/02/04 17:21:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size_vars)
	{
		free(env->vars[i]);
		i++;
	}
	free(env->vars);
	free(env);
}

void	errors_env(void)
{
	perror(ERROR_ENV_MESS);
	exit(EXIT_FAILURE); // Gerer potentiellement le "$?"
}
