/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/23 14:55:15 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


t_token *lexer(char *input, int *error_code)
{
    t_token *head = NULL;
    int i = 0;
    t_error_info error = {LEXER_SUCCESS, NULL, 0};

    while (input[i])
    {
        if (process_token(&head, input, &i, &error) == -1)
        {
            *error_code = error.code;
            free_token_list(head);
            return (NULL);
        }
    }
    *error_code = error.code;
    return (head);
}

int process_token(t_token **head, char *input, int *i, t_error_info *error)
{
    skip_whitespace(input, i);
    if (!input[*i])
        return (1);

    if (is_operator(input[*i]))
    {
        if (!validate_operator(input, *i, error))
            return (-1);
        return (process_operator(head, input, i));
    }
    else if (is_quote(input[*i]))
    {
        return (process_quotes(head, input, i, error));
    }
    else if (input[*i] == '$' && !is_escaped(input, *i))
    {
        if (!validate_env_var(input, *i, error))
            return (-1);
        t_token *token = create_env_var_token(input, i);
        if (!token)
            return (-1);
        add_token(head, token);
        return (1);
    }
    else
    {
        return (process_word(head, input, i));
    }
}

void skip_whitespace(char *input, int *i)
{
    while (input[*i] && is_whitespace(input[*i]))
        (*i)++;
}

int is_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}
