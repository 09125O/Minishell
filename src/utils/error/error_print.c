/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:57:56 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 11:32:46 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	print_str_fd(char *str, int fd)
{
	if (str)
		ft_putstr_fd(str, fd);
}

void	print_error(const char *cmd, const char *arg, const char *message)
{
	ft_putstr_fd("minishell: ", 2);
	print_str_fd((char *)cmd, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		print_str_fd((char *)arg, 2);
	}
	if (message)
	{
		ft_putstr_fd(": ", 2);
		print_str_fd((char *)message, 2);
	}
	ft_putchar_fd('\n', 2);
}

void	print_syntax_error(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	print_str_fd((char *)token, 2);
	ft_putstr_fd("'\n", 2);
}

void	print_command_error(const char *cmd, const char *error)
{
	ft_putstr_fd("minishell: ", 2);
	print_str_fd((char *)cmd, 2);
	ft_putstr_fd(": ", 2);
	print_str_fd((char *)error, 2);
	ft_putchar_fd('\n', 2);
}
