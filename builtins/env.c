/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:15:45 by root              #+#    #+#             */
/*   Updated: 2025/02/05 17:16:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **env) //sera ajouter ensuite avec la partie env ( et le tableau sera modifier par un t_env)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
