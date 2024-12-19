/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:34:03 by niperez           #+#    #+#             */
/*   Updated: 2024/05/22 16:41:06 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*smap;

	i = 0;
	smap = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (smap == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		smap[i] = f(i, s[i]);
		i++;
	}
	smap[i] = '\0';
	return (smap);
}
