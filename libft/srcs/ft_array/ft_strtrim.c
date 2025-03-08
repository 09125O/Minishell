/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include <stdlib.h>
int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	if (c == 0)
		return ((char *)&str[i]);
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (size < 1)
		return (srclen);
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	end;
	char	*trim_str;

	i = 0;
	end = ft_strlen(s1);
	trim_str = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_strrchr(set, s1[i]))
		i++;
	while (i < end && ft_strrchr(set, s1[end - 1]))
		end--;
	trim_str = (char *)malloc((end - i + 1) * sizeof(char));
	if (!trim_str)
		return (NULL);
	ft_strlcpy(trim_str, &s1[i], (end - i + 1));
	return (trim_str);
}
/*
#include <stdio.h>
int main()
{
	char	s_origin[] = "yo!U! My friend!yo";
	char	set[] = "yo";
	char	*result;

	result = ft_strtrim(s_origin, set);
	printf("%s\n", result);
}
*/
