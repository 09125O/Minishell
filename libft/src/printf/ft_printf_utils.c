/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_spdiux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:12:32 by niperez           #+#    #+#             */
/*   Updated: 2024/06/10 12:16:54 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_pointer(unsigned long long ptr, int *count)
{
	if (!ptr)
		print_str("(nil)", count);
	else
	{
		print_str("0x", count);
		print_number(ptr, "0123456789abcdef", 16, count);
	}
}

void	print_integer(int n, int *count)
{
	if (n < 0)
	{
		print_char('-', count);
		print_number((unsigned int)(-n), "0123456789", 10, count);
	}
	else
		print_number((unsigned int)n, "0123456789", 10, count);
}

void	print_unsigned_int(unsigned int n, int *count)
{
	print_number(n, "0123456789", 10, count);
}

void	print_hex(unsigned int n, int is_upper_case, int *count)
{
	if (is_upper_case)
		print_number(n, "0123456789ABCDEF", 16, count);
	else
		print_number(n, "0123456789abcdef", 16, count);
}

void	print_number(unsigned long long n, char *base, size_t size, int *count)
{
	if (n < size)
		print_char(base[n], count);
	else
	{
		print_number(n / size, base, size, count);
		print_char(base[n % size], count);
	}
}
