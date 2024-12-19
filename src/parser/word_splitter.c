/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:51:34 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:37:10 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "libft.h"

static int	count_words(char *str)
{
   int		count;
   int		i;
   char	quote;

   count = 0;
   i = 0;
   while (str[i])
   {
   	while (str[i] && is_whitespace(str[i]))
   		i++;
   	if (str[i])
   	{
   		count++;
   		quote = get_quote_type(str[i]);
   		if (quote)
   			find_closing_quote(str, &i, quote);
   		while (str[i] && !is_whitespace(str[i]))
   			i++;
   	}
   }
   return (count);
}

static int	get_word_len(char *str)
{
   int		len;
   char	quote;

   len = 0;
   while (str[len] && !is_whitespace(str[len]))
   {
   	quote = get_quote_type(str[len]);
   	if (quote)
   	{
   		len++;
   		while (str[len] && str[len] != quote)
   			len++;
   		len++;
   	}
   	else
   		len++;
   }
   return (len);
}

static char	*extract_one_word(char *str, int *i)
{
   char	*word;
   int		len;
   int		j;

   len = get_word_len(&str[*i]);
   word = malloc(sizeof(char) * (len + 1));
   if (!word)
   	return (NULL);
   j = 0;
   while (j < len)
   	word[j++] = str[(*i)++];
   word[j] = '\0';
   return (word);
}

char	**split_words(char *str)
{
   char	**words;
   int		word_count;
   int		i;
   int		j;

   if (!str)
   	return (NULL);
   word_count = count_words(str);
   words = malloc(sizeof(char *) * (word_count + 1));
   if (!words)
   	return (NULL);
   i = 0;
   j = 0;
   while (j < word_count)
   {
   	while (str[i] && is_whitespace(str[i]))
   		i++;
   	words[j] = extract_one_word(str, &i);
   	if (!words[j++])
   		return (free_word_array(words), NULL);
   }
   words[j] = NULL;
   return (words);
}

void	free_word_array(char **words)
{
   int	i;

   if (!words)
   	return ;
   i = 0;
   while (words[i])
   	free(words[i++]);
   free(words);
}
