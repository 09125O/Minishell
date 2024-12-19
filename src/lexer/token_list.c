/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:48:21 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/18 00:27:38 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

t_token	*create_token(char *value, t_token_type type)
{
   t_token	*token;

   token = malloc(sizeof(t_token));
   if (!token)
   	return (NULL);
   token->value = value;
   token->type = type;
   token->next = NULL;
   return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
   t_token	*last;

   if (!new_token)
   	return ;
   if (!*head)
   {
   	*head = new_token;
   	return ;
   }
   last = get_last_token(*head);
   last->next = new_token;
}

t_token	*get_last_token(t_token *head)
{
   t_token	*current;

   if (!head)
   	return (NULL);
   current = head;
   while (current->next)
   	current = current->next;
   return (current);
}

void	free_token_list(t_token *token)
{
   t_token	*next;

   while (token)
   {
   	next = token->next;
   	if (token->value)
   		free(token->value);
   	free(token);
   	token = next;
   }
}
