/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** CHECK ALL NODES NULL
 * Checks if all nodes in the linked list have NULL values,
 * @return 1 if found NULL value
 * @return 0 if found non-NULL value.
 */
int	prs_check_allnodes_null(t_token *token)
{
	while (token)
	{
		if (token->value)
			return (SUCCESS);
		token = token->next;
	}
	return (FAILURE);
}

/** PRS_REMOVE_NODE_NULL
 * (1) Initialize 'token' to point to the head of the list
 * (2) Loop & handle NULL values at the beginning of the list -> Loop + delete
 * (3) Loop & handle NULL not at the beginning of the list -> Loop + delete;
 *     If not NULL-> continue loop
 * @note *head = token;
 * Update head pointer to new start of linked list after remove initial NULL node
 *
 */
int	prs_remove_node_null(t_token **head)
{
	t_token	*current;
	t_token	*token;

	token = (*head);
	while (token != NULL && token->value == NULL)
	{
		current = token;
		token = token->next;
		free(current);
	}
	*head = token;
	while (token != NULL && token->next != NULL)
	{
		if (token->next->value == NULL)
		{
			current = token->next;
			token->next = token->next->next;
			free(current);
		}
		else
			token = token->next;
	}
	return (SUCCESS);
}

/** PRS_HANDLE_CMD
 * - (1) Loop to check if it's string -> Mark as command
 * - (2) Process any tokens that follow until a PIPE or the end of the list
 * - (3) If it's STR (an argument) -> mark as "ARG" type
 * @note 
 *  if (token != NULL) : extra protection conditon at end of while loop
 * -> prevent looping til one after NULL
 * EX:
 * echo "Hello, world" > output.txt | cat -n output.txt
 */
int	prs_handle_cmd(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == STR)
		{
			token->type = COMMAND;
			while (token != NULL && token->type != PIPE)
			{
				if (token->type == STR)
					token->type = ARG;
				token = token->next;
			}
		}
		if (token != NULL)
			token = token->next;
	}
	return (SUCCESS);
}

/** PRS_UNLINK ERROR
 * - Iterates through a linked list of t_token nodes,
 * - When encounters a node with a specific type (NON_HEREDOC),
 * -> Unlinks (deletes) a file whose path is stored
 *    in the value field of the next node
 * @note
 * unlink():
 * - Delete temporary files associated with here-documents
 * - Ensures that these temporary files are properly removed
*/
void	prs_unlink_error(t_token *token)
{
	while (token)
	{
		if (token->type == NON_HEREDOC)
			unlink(token->next->value);
		token = token->next;
	}
}

/** PARSING */
int	parsing(t_token **token)
{
	int	return_code;

	return_code = 0;
	if (prs_check_quotes_valid(*token) != 0)
		return_code = FAILURE;
	else if (prs_handle_quotes_n_expand_env(*token) != 0)
		return_code = FAILURE;
	else if (prs_remove_node_null(token) != 0)
		return_code = FAILURE;
	else if (prs_check_allnodes_null(*token) != 0)
		return_code = FAILURE_VOID;
	else if (prs_handle_redir(*token) != 0)
		return_code = FAILURE;
	else if (prs_handle_cmd(*token) != 0)
		return_code = FAILURE;
	else if (prs_handle_heredoc(*token) != 0)
	{
		prs_unlink_error(*token);
		return_code = FAILURE_VOID;
	}
	return (return_code);
}
