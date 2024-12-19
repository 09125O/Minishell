/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:47:54 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/19 18:41:50 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

static int	get_word_length(char *input, int i)
{
	int		len;
	char	quote;

	len = 0;
	while (input[i] && is_word_char(input[i]))
	{
		if ((input[i] == '"' || input[i] == '\''))
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
			{
				len++;
				i++;
			}
			if (input[i])
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*extract_word(char *input, int *i, int *status)
{
	int		len;
	int		j;
	char	*word;
	char	quote;

	*status = 0;
	len = get_word_length(input, *i);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (*status = 1, NULL);
	j = 0;
	while (j < len)
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				word[j++] = input[(*i)++];
			if (input[*i])
				(*i)++;
		}
		else
			word[j++] = input[(*i)++];
	}
	word[j] = '\0';
	return (word);
}

t_token	*create_word_token(char *input, int *i)
{
	char	*word;
	t_token	*token;
	int		status;

	status = 0;
	word = extract_word(input, i, &status);
	if (!word)
		return (NULL);
	token = create_token(word, TOKEN_WORD);
	if (!token)
	{
		free(word);
		return (NULL);
	}
	return (token);
}

t_token	*create_operator_token(char *input, int *i)
{
	t_token_type	type;
	t_token			*token;

	type = get_token_type(input, i);
	token = create_token(NULL, type);
	if (!token)
		return (NULL);
	return (token);
}