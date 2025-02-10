/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:51:34 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 22:26:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"

static int count_words(char *str)
{
    int count = 0;
    int i = 0;
    while (str[i])
	{
        while (str[i] && is_whitespace(str[i]))
            i++;
        if (str[i])
		{
            count++;
            char quote = get_quote_type(str[i]);
            if (quote)
				find_closing_quote(str, &i, quote);
            while (str[i] && !is_whitespace(str[i]))
                i++;
        }
    }
    return (count);
}

static int get_word_len(char *str)
{
    int len = 0;
    while (str[len] && !is_whitespace(str[len]))
	{
        char quote = get_quote_type(str[len]);
        if (quote)
		{
            len++;
            while (str[len] && str[len] != quote)
                len++;
            len++;
        }
		else
		{
            len++;
        }
    }
    return (len);
}

static char *extract_one_word(char *str, int *i)
{
    int len = get_word_len(&str[*i]);
    char *word = malloc(len + 1);
    if (!word)
		return (NULL);
    int j = 0;
    while (j < len)
        word[j++] = str[(*i)++];
    word[j] = '\0';
    return (word);
}

char **split_words(char *str)
{
    if (!str)
		return (NULL);
    int word_count = count_words(str);
    char **words = malloc(sizeof(char *) * (word_count + 1));
    if (!words)
		return (NULL);
    int i = 0;
    int j = 0;
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

void free_word_array(char **words)
{
    if (!words)
		return;
    int i = 0;
    while (words[i])
	{
        free(words[i]);
        i++;
    }
    free(words);
}
