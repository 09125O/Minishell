/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:11:07 by root              #+#    #+#             */
/*   Updated: 2025/02/04 17:11:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	strs = (char *)malloc(sizeof(*strs) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (strs == 0)
		return (NULL);
	while (s1[i])
	{
		strs[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strs[i] = s2[j];
		j++;
		i++;
	}
	strs[i] = '\0';
	return (strs);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*str;

	if (start >= ft_strlen(s))
		size = 0;
	else if (start + len > ft_strlen(s))
		size = ft_strlen(s) - start;
	else
		size = len;
	str = malloc(sizeof (char) * (size + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i != size)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
