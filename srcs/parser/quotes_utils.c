/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** PRS_GET_QUOTED_STR
 * (1) Calculate the length of the quoted string (excluding the closing quote)
 * (2)  Default to DOUBLEQUOTE type
 * (3) Check if inside the quote has context
 * [IF] has context  -> Create a token starting after the opening quote (`str
	+ 1`) of the given length
 * [ELSE] NO context -> Inside the quotes, create an empty string token
 * @note
 * len = ft_quotes_len(input_str, c) - 1; => skip closing quote (ft_quotes_len)
 * new_token = creat_token("\0", 1, STR, content):
 * "\0": represent an empty string (null-terminated), a string with no content
 */
t_token	*prs_get_quoted_str(char *input_str, char c, t_shell *content)
{
	int				len;
	t_token			*new_token;
	t_token_type	type;

	if (!input_str || ft_quotes_len(input_str, c) <= 1)
		return (NULL);
	len = ft_quotes_len(input_str, c) - 1;
	new_token = NULL;
	type = DBL_QUOTE;
	if (c == '\'')
		type = SGL_QUOTE;
	if (len > 0)
		new_token = token_create(input_str + 1, len, type, content);
	else
		new_token = token_create("\0", 1, STR, content);
	return (new_token);
}

/** FT_QUOTES_LEN
 * Calculate the length of a quoted substring ("..." or '...')
 * @param sd_quote : single or double quote
 * - Start after the opening quote,
 * - Continues until it finds the matching closing quote
 * @note
 * len = 1; (skip the first quote sign)!  
 */
int	ft_quotes_len(char *str, char sd_quote)
{
	int	len;

	len = 1;
	while (str[len] && str[len] != sd_quote)
		len++;
	return (len);
}

/** FT_ROGUE_LEN*/
int	ft_rogue_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '\'' || str[len] == '\"')
			break ;
		len++;
	}
	return (len);
}
