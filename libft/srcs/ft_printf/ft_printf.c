/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//check_format
static int	check_format(const char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_put_char(va_arg(args, int));
	else if (specifier == 's')
		count += ft_put_str(va_arg(args, char *));
	else if (specifier == 'p')
		count += ft_put_ptr(va_arg(args, void *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_put_int(va_arg(args, int));
	else if (specifier == 'u')
		count += ft_put_unsign(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		count += ft_put_hex(va_arg(args, unsigned int), specifier);
	else if (specifier == '%')
		return ((int)write(1, &specifier, 1));
	else
		count = -1;
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		print_len;
	va_list	args;

	print_len = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				print_len += check_format(*format, args);
			else
				return (-1);
		}
		else
			print_len += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (print_len);
}
