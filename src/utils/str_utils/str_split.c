/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:57:41 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 11:30:05 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count_words(const char *str, char sep)
{
   int	count;
   int	i;

   count = 0;
   i = 0;
   while (str[i])
   {
   	while (str[i] && str[i] == sep)
   		i++;
   	if (str[i])
   		count++;
   	while (str[i] && str[i] != sep)
   		i++;
   }
   return (count);
}

static char	*get_next_word(const char *str, char sep, int *pos)
{
   char	*word;
   int		start;
   int		i;

   while (str[*pos] && str[*pos] == sep)
   	(*pos)++;
   start = *pos;
   while (str[*pos] && str[*pos] != sep)
   	(*pos)++;
   word = malloc((*pos - start + 1) * sizeof(char));
   if (!word)
   	return (NULL);
   i = 0;
   while (start < *pos)
   	word[i++] = str[start++];
   word[i] = '\0';
   return (word);
}

char	**split_by_char(char *str, char sep)
{
   char	**result;
   int		words;
   int		pos;
   int		i;

   if (!str)
   	return (NULL);
   words = count_words(str, sep);
   result = malloc((words + 1) * sizeof(char *));
   if (!result)
   	return (NULL);
   pos = 0;
   i = 0;
   while (i < words)
   {
   	result[i] = get_next_word(str, sep, &pos);
   	if (!result[i])
   	{
   		free_str_array(result);
   		return (NULL);
   	}
   	i++;
   }
   result[words] = NULL;
   return (result);
}
