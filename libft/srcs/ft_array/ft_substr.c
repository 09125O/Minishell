/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
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
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*sub_str;

	i = 0;
	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= s_len)
		return (ft_strdup(""));
	else if (len > (s_len - start))
		len = s_len - start;
	sub_str = (char *)malloc((len + 1) * sizeof(*s));
	if (!sub_str)
		return (NULL);
	while (s[start + i] && i < len)
	{
			sub_str[i] = s[start + i];
			i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char	main_s[] = "12345678910!!PACO LET ME PASS!!!";
	// char	sub_s[] = "C'est";
	char	*result = ft_substr(main_s, 11, (strlen(main_s) + 1));
	printf("%s\n", result);
}
*/
