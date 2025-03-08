/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int	ft_putchar(char a);
// #include <unistd.h>
// int	ft_putchar(char a)
// {
// 	return (write(1, &a, 1));
// }

int	ft_put_int(long int nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count += ft_put_char('-');
		nb = nb * (-1);
	}
	if (nb >= 10)
	{
		count += ft_put_int(nb / 10);
		count += ft_put_int(nb % 10);
	}
	else
		count += ft_put_char(nb + 48);
	return (count);
}
// #include <stdio.h>
// int main()
// {
// 	int	test;

// 	test = ft_printf_int(-123456);
// 	// printf("test: %i\n", test);
// }