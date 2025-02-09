/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:51:05 by root              #+#    #+#             */
/*   Updated: 2025/02/09 16:53:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(char **args, char **env)
{
	int	i;
	int	status;

	status = 0;
	if (!args || !env)
		return (1);
	i = 1;
	while (args[i])
	{
		if (ft_remove_env(args[i], env) == -1) //sera ajouter ensuite avec la partie env
		{
			ft_error("unset", args[i], "not a valid identifier");
			status = 1;
		}
		i++;
	}
	return (status);
}