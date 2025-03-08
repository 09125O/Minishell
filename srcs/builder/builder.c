/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** INIT BUILD */
t_exec	*init_build(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = NULL;
	new->redirs = NULL;
	new->next = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	return (new);
}

/** BD_HANDLE_PIPE
 * @note Input token list:
 * [CMD: "ls"] -> [PIPE] -> [CMD: "grep file"] -> [PIPE] -> [CMD: "wc -l"]
 * @note Recursion will build:
 * exec (cmd: "ls", next: exec(cmd: "grep file", next: exec(cmd: "wc -l")))
 */
int	bd_handle_pipe(t_exec *exec, t_token *token)
{
	if (token->type == PIPE)
	{
		exec->next = build_to_exec(token->next);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	bd_handle_cmd(t_exec *exec, t_token *token)
{
	if (token->type == COMMAND)
	{
		exec->cmd = ft_strdup(token->value);
		if (!exec->cmd)
			return (FAILURE);
	}
	return (SUCCESS);
}

/** BUILD_TO_EXEC
 * Build a `t_exec` structure from the linked list of tokens.
 * (1) Initialize the `t_exec` structure; If fail -> return NULL
 * (2) Loop thru token list
 * -1 Handle PIPE
	->  Recursively creating a new `t_exec` structure for the next command.
 * -2 Handle COMMAND -> Storing its value in the `cmd` field.
 * -3 Handle redirection tokens
 * -4 Handle argument tokens
 * @note if (bd_handle_pipe(exec, token) == FAILURE) -> NEED break
 * -> Loop would continue process tokens that belong to next command segment,
 * which is incorrect cuz the tokens should be handled by the recursive call
 * @note if (handle_command(exec, token)) -> NEED return NULL
 * -> If memory allocation fails,
 * the program need stop processing the current segment
 * to avoid undefined behavior or memory leaks.
 * @return constructed `t_exec` structure -> to proceed exec
 */
t_exec	*build_to_exec(t_token *token)
{
	t_exec	*exec;

	exec = init_build();
	if (!exec)
		return (NULL);
	while (token != NULL)
	{
		if (bd_handle_pipe(exec, token) == FAILURE)
			break ;
		if (bd_handle_cmd(exec, token) == FAILURE)
			return (NULL);
		bd_handle_redirs(exec, token);
		bd_handle_args(exec, token);
		token = token->next;
	}
	return (exec);
}
