/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:08:41 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/19 12:16:05 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdlib.h>

static int	process_operator(t_token **head, char *input, int *i)
{
	t_token	*new_token;

	new_token = create_operator_token(input, i);
	if (!new_token)
		return (-1);
	add_token(head, new_token);
	(*i)++;
	return (0);
}

static int	process_word(t_token **head, char *input, int *i)
{
	t_token	*new_token;

	new_token = create_word_token(input, i);
	if (!new_token)
		return (-1);
	add_token(head, new_token);
	return (0);
}

static int	process_token(t_token **head, char *input, int *i)
{
	skip_whitespace(input, i);
	if (!input[*i])
		return (1);
	if (is_operator(input[*i]))
		return (process_operator(head, input, i));
	return (process_word(head, input, i));
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;
	int		status;

	if (!input)
		return (NULL);
	i = 0;
	head = NULL;
	while (input[i])
	{
		status = process_token(&head, input, &i);
		if (status == -1)
			return (free_token_list(head), NULL);
		if (status == 1)
			break ;
	}
	return (head);
}