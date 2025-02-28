/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:45:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 14:16:11 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"

int	ft_unset(char **args, t_env *env)
{
	int	i;
	int	ret;

	if (!args[1])
		return (0);
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (!env_is_valid_key(args[i]))
		{
			ft_error("unset", args[i], "invalid parameter name");
			ret = 1;
		}
		else
			env_remove(&env, args[i]);
		i++;
	}
	return (ret);
}
