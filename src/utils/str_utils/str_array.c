/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:57:03 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 00:08:14 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	str_array_len(char **array)
{
   int	len;

   if (!array)
   	return (0);
   len = 0;
   while (array[len])
   	len++;
   return (len);
}

void	free_str_array(char **array)
{
   int	i;

   if (!array)
   	return ;
   i = 0;
   while (array[i])
   {
   	free(array[i]);
   	i++;
   }
   free(array);
}

static char	*dup_str_secure(char *str)
{
   if (!str)
   	return (NULL);
   return (ft_strdup(str));
}

char	**dup_str_array(char **array)
{
   char	**new;
   int		i;

   if (!array)
   	return (NULL);
   new = ft_calloc(str_array_len(array) + 1, sizeof(char *));
   if (!new)
   	return (NULL);
   i = 0;
   while (array[i])
   {
   	new[i] = dup_str_secure(array[i]);
   	if (!new[i])
   	{
   		free_str_array(new);
   		return (NULL);
   	}
   	i++;
   }
   return (new);
}
