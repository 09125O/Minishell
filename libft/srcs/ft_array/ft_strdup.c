/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdlib.h>*/

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		srclen;
	int		i;

	srclen = ft_strlen(src);
	dest = (char *)malloc((srclen + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
#include <stdio.h>
int	main(int ac, char *av[])
{
	char	*dup;

	if (ac == 3)
	{
		printf("%s\n", av[1]);
		dup = ft_strdup(av[2]);

		if (dup)
		{
			printf("%s\n", dup);
			free(dup);
		}
	}
	return (0);
}
*/
