/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:51:05 by root              #+#    #+#             */
/*   Updated: 2025/02/10 13:21:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(char **args, t_env *env)
{
	int	i;
	int	status;

	status = 0;
	if (!args || !env)
		return (1);
	i = 1;
	while (args[i])
	{
		if (remove_env_var(env, args[i]) == -1) //ne le detecte pas
		{
			ft_error("unset", args[i], "not a valid identifier");
			status = 1;
		}
		i++;
	}
	return (status);
}