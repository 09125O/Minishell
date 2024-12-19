/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:50:32 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:40:16 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include "libft.h"

char	get_quote_type(char c)
{
   if (c == '"' || c == '\'')
   	return (c);
   return (0);
}

int	find_closing_quote(const char *str, int *i, char quote)
{
   int	start;

   start = *i;
   (*i)++;
   while (str[*i] && str[*i] != quote)
   	(*i)++;
   if (!str[*i])
   {
   	*i = start;
   	return (0);
   }
   return (1);
}

static int	count_char_without_quotes(char *str)
{
   int		count;
   int		i;
   char	quote;

   count = 0;
   i = 0;
   while (str[i])
   {
   	quote = get_quote_type(str[i]);
   	if (quote)
   	{
   		if (!find_closing_quote(str, &i, quote))
   			return (-1);
   		i++;
   	}
   	else
   	{
   		count++;
   		i++;
   	}
   }
   return (count);
}

int	is_quoted(char *str)
{
   int	i;

   i = 0;
   while (str[i] && !get_quote_type(str[i]))
   	i++;
   return (str[i] != '\0');
}

char	*handle_quotes(char *str)
{
   char	*result;
   int		i;
   int		j;
   char	quote;

   i = 0;
   j = 0;
   result = malloc(sizeof(char) * (count_char_without_quotes(str) + 1));
   if (!result)
   	return (NULL);
   while (str[i])
   {
   	quote = get_quote_type(str[i]);
   	if (quote && find_closing_quote(str, &i, quote))
   		i++;
   	else
   		result[j++] = str[i++];
   }
   result[j] = '\0';
   return (result);
}
