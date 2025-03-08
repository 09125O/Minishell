/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <unistd.h>*/

void	*ft_memchr(const void *str, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)str;
	while (i < n)
	{
		if ((unsigned char)ptr[i] == (unsigned char)c)
			return ((char *)&ptr[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char	str[] = "late!wanna~go~home!";
	char	*result;
	char	*result_r;

	result = ft_memchr(str, 'g', 50);
	printf("%s\n", result);
	result_r = memchr(str, 'g', 50);
	printf("%s\n", result_r);
	return (0);
}
*/