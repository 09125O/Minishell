/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** LEX_TOKENIZE_EACH_WD
 * - Extract and labels individual tokens
 * - Identifies a single token based on its type and length
 * @note
 * Scope: Handle only one word or symbol at a time!!!
 * (Like reading one word at a time without considering whole sentence)
 * @return (single token)
 */
t_token	*lex_tokenize_each_wd(char *str, t_shell *content)
{
	t_token			*new_token;
	t_token_type	token_type;
	int				token_len;

	new_token = NULL;
	token_type = lex_get_token_meta_type(str);
	token_len = lex_ft_1tokenlen(str, token_type);
	new_token = token_create(str, token_len, token_type, content);
	return (new_token);
}

/** LEXING
 * Read / process through the entire input line
 * Call lex_tokenize_each_wd() when encounter meaningful word/symbol
 * Use lex_tokenize_each_wd() repeatedly to form a structured list of tokens
 * @note
 * - Frees any tokens created so far and returns NULL to indicate an error.
 * - If the character is not a space or tab, process it as a token
 * - lex_tokenize_each_wd(&(input_line[i]), content);
 * "&(input_line[i])" instead of "input_line": 
 * -> Iterate to process each character one by one
 * @return  A linked list of tokens,
 * -> represent entire line as a sequence of categorized words or symbols
 */
t_token	*lexing(t_shell *content, char *input_line)
{
	t_token	*token;
	t_token	*current;
	int		i;

	i = 0;
	token = NULL;
	while (input_line[i])
	{
		if (input_line[i] == ' ' || input_line[i] == '\t')
			i++;
		else
		{
			current = lex_tokenize_each_wd(&(input_line[i]), content);
			if (!current)
			{
				token_free(token);
				return (NULL);
			}
			token_add_back(&token, current);
			i += ft_strlen(current->value);
		}
	}
	return (token);
}
