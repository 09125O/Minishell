/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:22:38 by niperez           #+#    #+#             */
/*   Updated: 2024/06/10 12:17:22 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	print_str(char *str, int *count)
{
	if (str == NULL)
		str = "(null)";
	while (*str != '\0')
	{
		print_char(*str, count);
		str++;
	}
}

static int	is_in(int c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static void	print_args(int c, va_list *args, int *count)
{
	if (c == 'c')
		print_char(va_arg(*args, int), count);
	else if (c == 's')
		print_str(va_arg(*args, char *), count);
	else if (c == 'p')
		print_pointer(va_arg(*args, unsigned long long), count);
	else if (c == 'd' || c == 'i')
		print_integer(va_arg(*args, int), count);
	else if (c == 'u')
		print_unsigned_int(va_arg(*args, unsigned int), count);
	else if (c == 'x')
		print_hex(va_arg(*args, unsigned int), 0, count);
	else if (c == 'X')
		print_hex(va_arg(*args, unsigned int), 1, count);
	else if (c == '%')
		print_char('%', count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (*str != '\0')
	{
		if (*str != '%')
			print_char(*str, &count);
		else
		{
			str++;
			if (is_in(*str, "cspdiuxX%"))
				print_args(*str, &args, &count);
			else
				return (va_end(args), -1);
		}
		str++;
	}
	va_end(args);
	return (count);
}
