/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/23 14:29:45 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int process_word(t_token **head, char *input, int *i)
{
    t_token *token = create_word_token(input, i);
    if (!token)
        return (-1);
    add_token(head, token);
    return (1);
}

int process_operator(t_token **head, char *input, int *i)
{
    t_token *token = create_operator_token(input, i);
    if (!token)
        return (-1);
    add_token(head, token);
    return (1);
}
