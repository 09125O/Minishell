/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** CREATE TOKEN
 * Creates a new token then initialize its properties based on provided values
 *
 * (1) Allocates Memory:  for a new token structure to hold the token's data
 * (2) Dup input_str by parts: strndup()
 * -> dup and saves this copy as the token's value
 * - (3) Label the token: store in t_token_type
 * - (4) Link content: It attaches any additional context,
	like where it came from, if needed.
 *
 * @param token_value: Point to start of token's value in the input_str
 * @param n: The number of characters to copy to the token's value.
 * @param type: The type of the token (e.g., STRING, COMMAND)
 * @param content: Provide additional info about the token's environment)
 *
 * EX:
 * - token_value: points to the h in "hello" in "echo hello"
 * - n:  n is 5 (the length of "hello"),
 */
t_token	*token_create(char *token_value, int n, t_token_type type,
		t_shell *content)
{
	t_token	*new_token;
	char	*dup_token_value;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	dup_token_value = ft_strndup(token_value, n);
	if (!dup_token_value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->value = dup_token_value;
	new_token->type = type;
	new_token->content = content;
	new_token->next = NULL;
	return (new_token);
}

/** TOKEN_ADD_BACK
 * - Add a new token to the end of a linked list of tokens.
 * - If the list is empty (head is NULL) -> Set the new token as the head.
 * @return (0) if successful / (1) if the new token is NULL.
 */
int	token_add_back(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return (FAILURE);
	if (!(*head))
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
	return (SUCCESS);
}

/**TOKEN_FREE
 * Frees an entire linked list of tokens:
 * - (1) value inside each token(node)
 * - (2) pointer to linked list
 */
void	token_free(t_token *head)
{
	t_token	*current;
	t_token	*tmp_next;

	current = head;
	while (current != NULL)
	{
		tmp_next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = tmp_next;
	}
}
