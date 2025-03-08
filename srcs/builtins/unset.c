/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 22:54:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/** ERROR UNSET */
void	error_unset(char *input_line)
{
	ft_putstr_fd(P_NAME, STDERR_FILENO);
	ft_putstr_fd(": unset: ", STDERR_FILENO);
	ft_putstr_fd(input_line, STDERR_FILENO);
	ft_putstr_fd(" : Not a valid identifier\n", STDERR_FILENO);
}

/** UNSET (with no options)
 * unset VAR1 VAR2 VAR3
 */
int	ft_unset(t_shell *content, t_arg *args)
{
	if (!args)
		return (SUCCESS);
	else
	{
		while (args)
		{
			if (delete_envvar(args->value, &(content->env)) != 0)
				return (FAILURE);
			args = args->next;
		}
	}
	return (SUCCESS);
}

/** DELETE_ENVVAR
 * BEFORE:
 * HEAD -> [USER=lin] -> [PATH=/bin] -> [SHELL=/bin/bash] -> NULL
 * AFTER:
 * HEAD -> [USER=lin] -> [SHELL=/bin/bash] -> NULL
 * (1) Find the node matching 'value' in the environment list
 * (2) If the node does not exist, return 0 (nothing to delete)
 * (3) If the node to delete == the first node in list,
 * => Update the head of the list to skip the node to be deleted
 * (4) If the node to delete != the first node in list,
 * => Skip to unlink the node
 *
 */
int	delete_envvar(char *env_id, t_env **env)
{
	t_env	*head;
	t_env	*to_delete;

	head = get_env(env_id, *env);
	if (!head)
		return (SUCCESS);
	if (*env == head)
		*env = head->next;
	else
	{
		to_delete = *env;
		while (to_delete->next != head)
			to_delete = to_delete->next;
		to_delete->next = head->next;
	}
	env_delete_1node(head);
	return (SUCCESS);
}

/** ENV_DELETE_1NODE
 * @note
 * - Safe to set if() conditions -> Avoid freeing NULL nodes
 * - Free(env) pointer to the whole structure at last
 * -> Remove the structure itself, de-allocate the pointer
 * -> prevent memory leak
 */
void	env_delete_1node(t_env *env)
{
	if (env->id)
		free(env->id);
	if (env->value)
		free(env->value);
	if (env->env_line)
		free(env->env_line);
	free(env);
}

/* OG
int	ft_unset(t_shell *content, t_arg *args)
{
	// if (!content->env || ft_env_lstsize(content->env) == 0)
	// 	return (SUCCESS);
	if (!args)
		return (SUCCESS);
	else
	{
		while (args)
		{
			if (delete_envvar(args->value, &(content->env)) != 0)
				return (FAILURE);
			args = args->next;
		}
	}
	return (SUCCESS);
}
/////////////////////
int	delete_envvar(char *env_value, t_env **env)
{
	t_env	*current;
	t_env	*to_delete;

	to_delete = get_env(env_value, *env);
	current = *env;
	if (!(*env))
		return (SUCCESS);
	if (!current)
		return (SUCCESS);
	if (to_delete == *env)
	{
		if (current->next)
		{
			current = current->next;
			*env = current;
		}
	}
	else
	{
		current = *env;
		while (current->next != to_delete)
			current = current->next;
		if (current->next->next)
			current->next = current->next->next;
		else
			current->next = NULL;
	}
	env_delete_1node(to_delete);
	return (SUCCESS);
}
*/
