/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/23 13:59:48 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

int is_word_char(char c)
{
    return (!is_whitespace(c) && !is_operator(c)) || c == '\\' || c == '$';
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

int is_escapable_char(char c)
{
    return (c == '\'' || c == '"' || c == '\\' || c == '|' ||
            c == '<' || c == '>' || c == ' ' || c == '$');
}

int is_escaped(char *input, int i)
{
    if (i > 0 && input[i - 1] == '\\')
    {
        // Vérifie si le \ lui-même n'est pas échappé
        if (i > 1 && input[i - 2] == '\\')
            return (0);
        return (1);
    }
    return (0);
}

int is_env_char(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') || c == '_');
}
