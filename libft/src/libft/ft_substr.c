/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:21:54 by niperez           #+#    #+#             */
/*   Updated: 2024/05/22 16:41:27 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;

	if (len > ft_strlen(s) - start)
		size = ft_strlen(s) - start;
	else
		size = len;
	if (start > ft_strlen(s))
	{
		size = 0;
		start = 0;
	}
	str = (char *) malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s + start, size + 1);
	return (str);
}
