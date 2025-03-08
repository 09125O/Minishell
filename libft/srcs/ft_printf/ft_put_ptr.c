/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// int	ft_putchar(char c);
// int	ft_putstr(char *str);

static int	ft_put_ptrhex(unsigned long int nb, char xX)
{
	char				*base;
	int					count;
	unsigned long int	base_len;

	count = 0;
	base_len = 16;
	if (xX == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nb < base_len)
		count += ft_put_char(base[nb % base_len]);
	else
	{
		count += ft_put_ptrhex(nb / base_len, xX);
		count += ft_put_ptrhex(nb % base_len, xX);
	}
	return (count);
}

int	ft_put_ptr(void *addr)
{
	int					count;
	unsigned long int	ptr;

	count = 0;
	ptr = (unsigned long int)addr;
	if (!ptr)
		return (ft_put_str("(nil)"));
	count += ft_put_str("0x");
	count += ft_put_ptrhex(ptr, 'x');
	return (count);
}

// #include <stdio.h>
// int main()
// {
// 	int result;
// 	unsigned long int	*test;

// 	result = ft_put_ptr(test);
// 	printf("%p\n", &result);
// }