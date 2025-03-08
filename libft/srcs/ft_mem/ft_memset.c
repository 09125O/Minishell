/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdlib.h>*/

void	*ft_memset(void *block, int value, size_t n)
{
	char	*ptr;

	ptr = (char *)block;
	while (n > 0)
	{
		ptr[n - 1] = value;
		n--;
	}
	return (block);
}
/*
#include <stdio.h>
int	main()
{
	char	str[5];

	ft_memset(str, 'A', 4);
	str[4] = '\0';
	printf("%s\n", str);
}
*/