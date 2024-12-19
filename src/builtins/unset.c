/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:27:05 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 19:24:24 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static int	is_valid_env_name(char *name)
{
   int	i;

   if (!name || !name[0] || ft_isdigit(name[0]))
   	return (0);
   i = 0;
   while (name[i])
   {
   	if (!ft_isalnum(name[i]) && name[i] != '_')
   		return (0);
   	i++;
   }
   return (1);
}

int	ft_unset(t_shell *shell, char **args)
{
   int	i;
   int	status;

   if (!args[1])
   	return (EXIT_SUCCESS);
   status = EXIT_SUCCESS;
   i = 1;
   while (args[i])
   {
   	if (!is_valid_env_name(args[i]))
   	{
   		print_error("unset", args[i], "not a valid identifier");
   		status = EXIT_FAILURE;
   	}
   	else
   		unset_env_var(&shell->env, args[i]);
   	i++;
   }
   return (status);
}
