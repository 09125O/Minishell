/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_strnstr(const char *long_str, const char *short_str, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (short_str[j] == '\0')
		return ((char *)long_str);
	while (long_str[i])
	{
		j = 0;
		while (long_str[i + j] == short_str[j] && (i + j) < len)
		{
			if (short_str[j + 1] == '\0')
				return ((char *)&long_str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main(void)
{
	char	lng_s[] = "hello,today!Saturday!";
	char	shrt_s[] = "Sa";
	char	lng_s_r[] = "hello,today!Saturday!";
	char	shrt_s_r[] = "Sa";
	char	*result;
	char	*result_real;

	result = ft_strnstr(lng_s, shrt_s, 14);
	printf("%s\n", result);	
	result_real = strnstr(lng_s_r, shrt_s_r, 14);
	printf("%s\n", result_real);	
}
*/
