/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:23:36 by niperez           #+#    #+#             */
/*   Updated: 2024/05/22 16:41:23 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, const char *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	size_t			end;
	size_t			len;

	start = 0;
	while (is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (is_in_set(s1[end], set))
		end--;
	len = end - start;
	return (ft_substr(s1, start, len + 1));
}
