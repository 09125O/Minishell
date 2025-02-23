/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/23 14:56:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int get_quoted_length(char *input, int i, char quote_type)
{
    int len = 0;
    i++; // Skip opening quote
    while (input[i + len] && input[i + len] != quote_type)
        len++;
    return (len);
}

char *extract_quoted_word(char *input, int *i, char quote_type, t_error_info *error)
{
    int len = get_quoted_length(input, *i, quote_type);
    if (!input[*i + len + 1]) // +1 pour la quote fermante
    {
        set_error(error, LEXER_ERROR_UNCLOSED_QUOTE, "Quote non fermée", *i);
        return (NULL);
    }

    char *word = malloc(len + 1);
    if (!word)
    {
        set_error(error, LEXER_ERROR_MEMORY, "Erreur d'allocation mémoire", *i);
        return (NULL);
    }

    (*i)++; // Skip opening quote
    int j = 0;
    while (j < len)
    {
        word[j] = input[*i + j];
        j++;
    }
    word[j] = '\0';
    *i += len + 1; // Skip content and closing quote

    return (word);
}

int process_quotes(t_token **head, char *input, int *i, t_error_info *error)
{
    char quote_type = input[*i];
    char *content = extract_quoted_word(input, i, quote_type, error);
    if (!content)
        return (-1);

    t_token *token = create_token(content,
        (quote_type == '"') ? TOKEN_DQUOTE : TOKEN_SQUOTE);
    if (!token)
    {
        free(content);
        set_error(error, LEXER_ERROR_MEMORY, "Erreur d'allocation mémoire", *i);
        return (-1);
    }

    add_token(head, token);
    return (1);
}
