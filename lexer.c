/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 22:54:01 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


t_token *lexer(char *input, int *error_code)
{
    t_token *head = NULL;
    int i = 0;
    *error_code = LEXER_SUCCESS;

    while (input[i])
    {
        if (process_token(&head, input, &i, error_code) == -1)
        {
            free_token_list(head);
            return (NULL);
        }
    }
    return (head);
}

static int process_token(t_token **head, char *input, int *i, int *error_code)
{
    skip_whitespace(input, i);
    if (!input[*i])
        return (1);

    if (is_operator(input[*i]))
    {
        return (process_operator(head, input, i));
    }
    else if (is_quote(input[*i]))
    {
        if (!find_closing_quote(input, i, input[*i]))
        {
            *error_code = LEXER_ERROR_UNCLOSED_QUOTE;
            return (-1);
        }
        return (process_word(head, input, i));
    }
    else
    {
        return (process_word(head, input, i));
    }
}

static void skip_whitespace(char *input, int *i)
{
    while (input[*i] && is_whitespace(input[*i]))
        (*i)++;
}

static int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}
