/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:47:54 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 20:37:14 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token *create_token(char *value, t_token_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
		return (NULL);
    token->value = value;
    token->type = type;
    token->next = NULL;
    return (token);
}

t_token *create_word_token(char *input, int *i)
{
    char *word = extract_word(input, i);
    if (!word)
		return (NULL);
    return (create_token(word, TOKEN_WORD));
}

t_token *create_operator_token(char *input, int *i)
{
    t_token_type type = get_token_type(input, i);
    return (create_token(NULL, type));
}

t_token_type get_token_type(char *input, int *i)
{
    if (input[*i] == '|') return (TOKEN_PIPE);
    if (input[*i] == '<') return (TOKEN_REDIRECT_IN);
    if (input[*i] == '>') return (TOKEN_REDIRECT_OUT);
    return (TOKEN_EOF);
}

int is_redirection(char c)
{
    return (c == '<' || c == '>');
}
