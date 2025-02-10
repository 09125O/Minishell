/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:47:54 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/10 20:44:36 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void add_token(t_token **head, t_token *new_token)
{
    if (!new_token)
	return;
    if (!*head)
	{
        *head = new_token;
        return;
    }
    t_token *last = get_last_token(*head);
    last->next = new_token;
}

t_token *get_last_token(t_token *head)
{
    if (!head)
		return (NULL);
    t_token *current = head;
    while (current->next)
        current = current->next;
    return (current);
}

void free_token_list(t_token *token)
{
    t_token *next;
    while (token)
	{
        next = token->next;
        if (token->value)
            free(token->value);
        free(token);
        token = next;
    }
}
