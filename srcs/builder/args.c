/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** BD_HANDLE_ARGS
 * - Process tokens representing arguments to a command 
 *  (e.g., filenames, options)
 * - Creates and appends each argument to the exec->args list
 */
int	bd_handle_args(t_exec *exec, t_token *token)
{
	t_arg	*new;

	new = NULL;
	if (token->type == ARG)
	{
		new = bd_args_create(token->value);
		if (!new)
			return (-1);
		arg_add_back(&(exec->args), new);
	}
	return (0);
}

/** BD_ARGS_CREATE */
t_arg	*bd_args_create(char *arg_value)
{
	t_arg	*args;
	char	*dup_arg;

	args = malloc(sizeof(t_arg));
	if (!args)
		return (NULL);
	dup_arg = ft_strdup(arg_value);
	if (!dup_arg)
	{
		free(args);
		return (NULL);
	}
	args->value = dup_arg;
	args->next = NULL;
	return (args);
}

/** BD_ARG_ADD_BACK */
int	arg_add_back(t_arg **head, t_arg *new)
{
	t_arg	*current;

	if (new == NULL)
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

/** ARG_FREE */
void	arg_free(t_arg *args)
{
	t_arg	*tmp;

	while (args != NULL)
	{
		tmp = args;
		if (args->value)
		{
			free(args->value);
			args->value = NULL;
		}
		args = args->next;
		free(tmp);
	}
}
