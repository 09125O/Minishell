/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, int nb)
{
	char	*new;
	int		i;
	int		len;

	i = 0;
	if (!str || nb < 0)
		return (NULL);
	if ((int)ft_strlen(str) <= nb)
		len = ft_strlen(str);
	else
		len = nb;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (str[i] && i < nb)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

// char	*ft_strndup(const char *src, int n)
// {
// 	char	*dest;
// 	int		srclen;
// 	int		i;

// 	srclen = ft_strlen(src);
// 	dest = (char *)malloc((srclen + 1) * sizeof(char));
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (src[i] && i < n)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }