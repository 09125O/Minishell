/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:47:39 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:27:22 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

int	is_whitespace(char c)
{
   return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
   return (c == '|' || c == '<' || c == '>');
}

void	skip_whitespace(char *input, int *i)
{
   while (input[*i] && is_whitespace(input[*i]))
   	(*i)++;
}

int	is_quote(char c)
{
   return (c == '\'' || c == '"');
}

int	is_word_char(char c)
{
   return (!is_whitespace(c) && !is_operator(c) && c != '\0');
}
