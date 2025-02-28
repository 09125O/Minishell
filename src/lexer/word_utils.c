/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:10:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 18:07:45 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "s_lexer.h"
#include "libft.h"

static int	is_assignment(char *input, int pos)
{
	while (pos > 0 && ft_isalnum(input[pos - 1]))
		pos--;
	while (input[pos] && ft_isalnum(input[pos]))
		pos++;
	return (input[pos] == '=');
}

static int	get_word_length(char *input, int *pos)
{
	int	len;
	int	in_quotes;
	int	is_var_assign;

	len = 0;
	in_quotes = 0;
	is_var_assign = is_assignment(input, *pos);

	while (input[*pos + len])
	{
		if (input[*pos + len] == '"' || input[*pos + len] == '\'')
		{
			if (!in_quotes)
				in_quotes = input[*pos + len];
			else if (in_quotes == input[*pos + len])
				in_quotes = 0;
		}
		if (!in_quotes && !is_var_assign && is_whitespace(input[*pos + len]))
			break;
		if (!in_quotes && !is_var_assign && is_operator(input[*pos + len]))
			break;
		if (!in_quotes && is_var_assign && input[*pos + len] == ' '
			&& !is_escaped(input, *pos + len - 1))
			break;
		len++;
	}
	return (len);
}

int	process_word(t_token **head, char *input, int *pos)
{
	int		len;
	char	*word;
	t_token	*token;

	len = get_word_length(input, pos);
	if (len == 0)
		return (0);

	word = ft_substr(input, *pos, len);
	if (!word)
		return (-1);

	token = create_token(TOKEN_WORD, word);
	if (!token)
	{
		free(word);
		return (-1);
	}

	add_token(head, token);
	*pos += len;
	return (1);
}

char	*extract_word(char *input, int *i)
{
	char	*word;
	int		len;
	int		j;
	int		k;

	len = get_word_length(input, i);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	j = *i;
	k = 0;
	while (k < len)
	{
		if (input[j] == '\\' && input[j + 1] && is_escapable_char(input[j + 1]))
		{
			word[k++] = input[j + 1];
			j += 2;
		}
		else
			word[k++] = input[j++];
	}
	word[k] = '\0';
	*i = j;
	return (word);
}

t_token	*create_word_token(char *input, int *i)
{
	char	*word;
	t_token	*token;

	word = extract_word(input, i);
	if (!word)
		return (NULL);
	token = create_token(TOKEN_WORD, word);
	if (!token)
	{
		free(word);
		return (NULL);
	}
	return (token);
}
