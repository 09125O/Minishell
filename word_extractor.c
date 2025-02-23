/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_extractor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/23 14:47:12 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int get_word_length(char *input, int i)
{
    int len = 0;
    while (input[i + len])
    {
        if (input[i + len] == '\\' && input[i + len + 1] && is_escapable_char(input[i + len + 1]))
        {
            len += 2;
            continue;
        }
        if (!is_word_char(input[i + len]) && !is_escaped(input, i + len))
            break;
        len++;
    }
    return (len);
}

char *extract_word(char *input, int *i)
{
    int len = get_word_length(input, *i);
    char *word = malloc(len + 1);
    if (!word)
        return (NULL);

    int j = 0;
    int k = 0;
    while (k < len)
    {
        if (input[*i + k] == '\\' && input[*i + k + 1] && is_escapable_char(input[*i + k + 1]))
        {
            k++;
            word[j++] = input[*i + k++];
            continue;
        }
        word[j++] = input[*i + k++];
    }
    word[j] = '\0';
    *i += len;
    return (word);
}
