/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/**	BD_HANDLE_REDIRS
 * - Add redirections to the redirs list in t_exec structure
 * - Process tokens representing redirections (e.g., >, >>, <, <<)
 * - Create + appends a redirection entry (target file OR heredoc content) 
 *   to the exec->redirs list
 * (1) Check if:
 * - The token has a valid next token (filename OR target of redirection)
 * - Current token type is redirs type(APPEND, HEREDOC, INFILE, OUTFILE)
 * (2) Create a new redir file structure with next token value
 * (3) Add to redirs list
 * 
 * @return
 * - BUILD_FAILURE (-1): Severe or unexpected error, 
 *   (often due to resource allocation failure or similar critical problems)
 * - SUCCESS (0): Function succeeded without issues
 * - FAILURE (1): General failure or expected failure condition
 * - FAILURE_VOID (2): Specific type of failure, 
 *   (possibly for a void return or non-critical issue)
 */

int	bd_handle_redirs(t_exec *exec, t_token *token)
{
	t_filename	*tmp;

	if (token->next && token->next->value != NULL && (token->type == APPEND
			|| token->type == NON_HEREDOC || token->type == INFILE
			|| token->type == OUTFILE))
	{
		tmp = bd_filenames_create(token->next->value, token->type);
		if (!tmp)
			return (BUILD_FAILURE);
		filename_add_back(&(exec->redirs), tmp);
		return (FAILURE);
	}
	return (SUCCESS);
}

/** bd_filenames_create
 * Create t_filename that stores the file path & the type of redirs
 * @param  t_filename *filename;
 * Pointer storing a t_filename structure to hold the redirection info
 * @param  char *new;
 * Pointer storing the duplicated string (path)
 * EX: < input.txt
 * - Call bd_filenames_create("input.txt", INFILE)
 * - Create a structure with the file path "input.txt" and type INFILE
 * EX: > output.txt
 * - Call bd_filenames_create("output.txt", OUTFILE) 
 * - Create a structure with the file path "output.txt" and type OUTFILE
 * @note Initialize the next pointer to NULL
 * -> Link to the next t_filename structure in a linked list if needed
 */
t_filename	*bd_filenames_create(char *pathname, t_token_type type)
{
	t_filename	*filename;
	char		*dup_path;

	filename = malloc(sizeof(t_filename));
	if (!filename)
		return (NULL);
	dup_path = ft_strdup(pathname);
	filename->path = dup_path;
	filename->type = type;
	filename->next = NULL;
	return (filename);
}

/** FILENAME_ADD_BACK
 * @note NO NEED set NULL after new!
 * -> in filename_creat() already attach NULL to new node
 */
int	filename_add_back(t_filename **head, t_filename *new)
{
	t_filename	*current;

	if (!new)
		return (FAILURE);
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	return (SUCCESS);
}

/** FILENAME_FREE */
void	filename_free(t_filename *filename)
{
	t_filename	*tmp;

	while (filename != NULL)
	{
		tmp = filename;
		if (filename->path)
			free(filename->path);
		filename = filename->next;
		free(tmp);
	}
}
