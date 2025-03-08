/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <unistd.h>*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s_ptr;
	unsigned char	*d_ptr;

	i = 0;
	d_ptr = (unsigned char *)dest;
	s_ptr = (unsigned char *)src;
	if (d_ptr < s_ptr)
	{
		while (i < n)
		{
			d_ptr[i] = s_ptr[i];
			i++;
		}
	}
	else if (d_ptr > s_ptr)
	{
		i = n;
		while (i > 0)
		{
			d_ptr[i - 1] = s_ptr[i - 1];
			i--;
		}
	}
	return (dest);
}
/*TEST FAILLLLLL
#include <stdio.h>
#include <string.h>
int	main()
{
	char	src[7] = "hello!";
	char	dest[7] = "WOO!";
	char	*result;
	char	*result_r;

	printf("src: %s\n", src);
	printf("dest: %s\n", dest);
	printf("=============\n");
	result = ft_memmove(dest, src, sizeof(src));
	printf("result: %s\n", result);
	result_r = memmove(dest, src, sizeof(src));
	printf("result_r: %s\n", result_r);
}
*/