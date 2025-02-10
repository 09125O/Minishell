/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 20:33:09 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

int is_word_char(char c)
{
    return (!is_whitespace(c) && !is_operator(c));
}

void skip_quotes(char *input, int *i)
{
    char quote = input[*i];
    (*i)++;
    while (input[*i] && input[*i] != quote)
        (*i)++;
    if (input[*i])
        (*i)++;
}
