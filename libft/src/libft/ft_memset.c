/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:39:56 by niperez           #+#    #+#             */
/*   Updated: 2024/05/22 16:40:13 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	val;

	i = 0;
	ptr = (unsigned char *) b;
	val = (unsigned char) c;
	while (i < len)
	{
		ptr[i] = val;
		i++;
	}
	return (b);
}
