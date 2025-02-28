/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:10:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/26 22:53:42 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_lexer.h"
#include "libft.h"

int	is_word_char(char c)
{
	return (!is_whitespace(c) && !is_operator(c) && !is_quote(c));
}

int	is_escapable_char(char c)
{
	return (c == '\\' || c == '\'' || c == '\"' || c == '$'
		|| c == ' ' || c == '\t' || c == '\n');
}

int	is_escaped(char *str, int pos)
{
	int	count;

	if (pos == 0)
		return (0);
	count = 0;
	pos--;
	while (pos >= 0 && str[pos] == '\\')
	{
		count++;
		pos--;
	}
	return (count % 2);
}

int	is_env_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

int	is_env_first_char(char c)
{
	return (ft_isalpha(c) || c == '_' || c == '?');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
