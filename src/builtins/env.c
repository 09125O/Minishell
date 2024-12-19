/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:27:22 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 19:18:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	print_env_var(t_env *env_var)
{
   ft_putstr_fd(env_var->key, 1);
   ft_putchar_fd('=', 1);
   if (env_var->value)
   	ft_putstr_fd(env_var->value, 1);
   ft_putchar_fd('\n', 1);
}

int	ft_env(t_shell *shell)
{
   t_env	*current;

   if (!shell || !shell->env)
   {
   	print_error("env", NULL, "environment not found");
   	return (EXIT_FAILURE);
   }
   current = shell->env;
   while (current)
   {
   	if (current->value)
   		print_env_var(current);
   	current = current->next;
   }
   return (EXIT_SUCCESS);
}
