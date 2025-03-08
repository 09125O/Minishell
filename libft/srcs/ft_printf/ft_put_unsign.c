/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int	ft_putchar(char a);
// int	ft_put_int(long int nb);
int	ft_put_unsign(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
	{
		count += ft_put_int(nb / 10);
		count += ft_put_int(nb % 10);
	}
	else
		count += ft_put_char(nb + 48);
	return (count);
}
