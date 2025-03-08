/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* OG strjoin; witout free*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*join_str));
	if (!join_str)
		return (NULL);
	while (s1[i])
	{
		join_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join_str[i + j] = s2[j];
		j++;
	}
	join_str[i + j] = '\0';
	return (join_str);
}
/* FOR get next line
char	*ft_strjoin(char *s1, char *s2)
{
	char	*joint_str;
	int		len1;
	int		len2;
	int		i;
	int		j;

	i = -1;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	joint_str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!joint_str)
		return (free(s1), NULL);
	while (s1[++i])
		joint_str[j++] = s1[i];
	i = -1;
	while (s2[++i])
		joint_str[j++] = s2[i];
	joint_str[j] = '\0';
	free(s1);
	return (joint_str);
}
*/
