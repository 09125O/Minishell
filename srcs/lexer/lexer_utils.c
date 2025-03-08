/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** CHECK_META_CHAR
 * Checks if the character is a meta character
 * ( |, <, >, single quotes, double quotes).
 * @return a non-zero value if is a meta character
 * -> to identify boundaries in tokens
 */
int	check_meta_char(char c)
{
	int	found;

	found = 0;
	if (c == '|')
		found = 1;
	else if (c == '<')
		found = 2;
	else if (c == '>')
		found = 3;
	else if (c == '\"')
		found = 4;
	else if (c == '\'')
		found = 5;
	return (found);
}

/** LEX_GET_TOKEN_META_TYPE
 * - Determine token type based on the first character of the string
 * - Checks for special characters like '<', '>', and '|' 
 * - Assign the corresponding token type
 * 
 * @return
 * HEREDOC if "<<"
 * APPEND if ">>"
 * Otherwise: INFILE, OUTFILE, PIPE, or STR
 */
t_token_type	lex_get_token_meta_type(char *input_str)
{
	if (input_str[0] == '>')
	{
		if (input_str[1] == '>')
			return (APPEND);
		else
			return (OUTFILE);
	}
	else if (input_str[0] == '<')
	{
		if (input_str[1] == '<')
			return (HEREDOC);
		else
			return (INFILE);
	}
	else if (input_str[0] == '|')
		return (PIPE);
	return (STR);
}

/** LEX FT_1TOKEN_LEN
 * - Count len of a token based on its type
 * - This len helps to identify how many characters to include in a token.
 * @param str: A pointer to the start of the token in the input string.
 * @param type: The type of the token 
 * (e.g., HEREDOC, APPEND, INFILE, OUTFILE, PIPE, STR)
 * @note
 * - INFILE (>), OUTFILE (<), or PIPE (|) => len = 1
 * - HEREDOC (<<) or APPEND (>>) => len = 2
 * - STR => ft_token_str_len()
 */
int	lex_ft_1tokenlen(char *str, t_token_type type)
{
	int	len;

	len = 0;
	if (type == INFILE || type == OUTFILE || type == PIPE)
		len = 1;
	else if (type == HEREDOC || type == APPEND)
		len = 2;
	else if (type == STR)
		len = ft_token_str_len(str);
	return (len);
}

/** FT_TOKEN_STRLEN
 * - Calculate the length of a "string" token (STR)
 * @note STR
 * - is any sequence of characters
 * - not a meta character
 * - does not contain spaces or tabs
 * @note
 * If meet quoted substrings -> skip over them
 */
int	ft_token_str_len(char *str)
{
	int	len;
	int	total_len;

	len = 0;
	total_len = ft_strlen(str);
	while (len < total_len)
	{
		if (str[len] == '\'')
			len += ft_quotes_len(&(str[len]), '\'');
		else if (str[len] == '\"')
			len += ft_quotes_len(&(str[len]), '\"');
		else if (check_meta_char(str[len]) || str[len] == '\t'
			|| str[len] == ' ')
			break ;
		len++;
	}
	return (len);
}
