/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:30:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 20:40:17 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include <stdlib.h>

int	ft_exit(char **args)
{
	int	status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);

	status = 0;
	if (args && args[1])
	{
		// Si le premier argument n'est pas un nombre
		if (!ft_isdigit_str(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			status = 2;
		}
		// Si le premier argument est un nombre
		else
		{
			status = ft_atoi(args[1]);
			// Si plus d'un argument
			if (args[2])
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
				return (1);  // Ne pas quitter si trop d'arguments
			}
		}
	}

	g_global.exit_status = status;
	return (EXIT_SHELL);  // Retourner une valeur spéciale pour indiquer qu'il faut quitter
}
