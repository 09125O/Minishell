/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:32:57 by niperez           #+#    #+#             */
/*   Updated: 2024/05/25 19:11:46 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return ((unsigned int) -n);
	else
		return ((unsigned int) n);
}

static size_t	ft_len(unsigned int nb)
{
	size_t	len;

	len = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				neg;
	size_t			len;
	size_t			nb;
	int				i;

	neg = n < 0;
	nb = ft_abs(n);
	len = ft_len(nb);
	str = (char *) malloc(sizeof(char) * (neg + len + 1));
	if (str == NULL)
		return (NULL);
	if (neg)
		str[0] = '-';
	str[len + neg] = '\0';
	i = neg + len - 1;
	while (nb > 9)
	{
		str[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	str[i] = nb + '0';
	return (str);
}
