/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:57:34 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 11:31:20 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*alloc_joined_str(char *s1, char *s2, char *sep)
{
   int		total_len;
   char	*result;

   total_len = 0;
   if (s1)
   	total_len += ft_strlen(s1);
   if (s2)
   	total_len += ft_strlen(s2);
   if (sep && s1 && s2)
   	total_len += ft_strlen(sep);
   result = malloc(sizeof(char) * (total_len + 1));
   if (!result)
   	return (NULL);
   result[0] = '\0';
   return (result);
}

char	*str_join_with_sep(char *s1, char *s2, char *sep)
{
   char	*result;

   result = alloc_joined_str(s1, s2, sep);
   if (!result)
   	return (NULL);
   if (s1)
   	ft_strlcat(result, s1, ft_strlen(s1) + 1);
   if (sep && s1 && s2)
   	ft_strlcat(result, sep, ft_strlen(result) + ft_strlen(sep) + 1);
   if (s2)
   	ft_strlcat(result, s2, ft_strlen(result) + ft_strlen(s2) + 1);
   return (result);
}

char	*str_join_three(char *s1, char *s2, char *s3)
{
   char	*temp;
   char	*result;

   temp = str_join_with_sep(s1, s2, NULL);
   if (!temp)
   	return (NULL);
   result = str_join_with_sep(temp, s3, NULL);
   free(temp);
   return (result);
}
