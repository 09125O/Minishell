/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:22:31 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 16:34:24 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

static void	print_args(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	n_option;

	if (!args || !args[1])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	i = 1;
	n_option = 0;
	while (args[i] && is_n_option(args[i]))
	{
		n_option = 1;
		i++;
	}
	print_args(args, i);
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (0);
}
