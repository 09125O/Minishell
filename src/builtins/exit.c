/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:27:34 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 21:02:20 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_valid_number(char *str)
{
   int	i;

   i = 0;
   if (str[i] == '+' || str[i] == '-')
   	i++;
   while (str[i])
   {
   	if (!ft_isdigit(str[i]))
   		return (0);
   	i++;
   }
   return (1);
}

static long	ft_atol(const char *str)
{
   long	result;
   int		sign;
   int		i;

   result = 0;
   sign = 1;
   i = 0;
   while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
   	i++;
   if (str[i] == '-' || str[i] == '+')
   {
   	if (str[i] == '-')
   		sign = -1;
   	i++;
   }
   while (str[i] >= '0' && str[i] <= '9')
   {
   	result = result * 10 + (str[i] - '0');
   	i++;
   }
   return (result * sign);
}

static int	check_exit_arg(char *arg)
{
   long	num;

   if (!is_valid_number(arg))
   {
   	print_error("exit", arg, "numeric argument required");
   	return (2);
   }
   num = ft_atol(arg);
   return ((unsigned char)num);
}

int	ft_exit(t_shell *shell, char **args)
{
   int	exit_code;

   ft_putendl_fd("exit", 2);
   if (!args[1])
   	exit_code = shell->exit_status;
   else if (args[2])
   {
   	print_error("exit", NULL, "too many arguments");
   	return (EXIT_FAILURE);
   }
   else
   	exit_code = check_exit_arg(args[1]);
   exit(exit_code);
}
