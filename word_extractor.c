/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_extractor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 20:31:35 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char *extract_word(char *input, int *i)
{
    int len = get_word_length(input, *i);
    char *word = malloc(len + 1);
    if (!word)
		return (NULL);
    int j = 0;
    while (j < len)
        word[j++] = input[(*i)++];
    word[j] = '\0';
    return (word);
}

static int get_word_length(char *input, int i)
{
    int len = 0;
    while (input[i + len] && is_word_char(input[i + len]))
        len++;
    return (len);
}

static int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

static int is_word_char(char c)
{
    return (!is_whitespace(c) && !is_operator(c));
}
