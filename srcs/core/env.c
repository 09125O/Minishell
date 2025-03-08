/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** GET_ENV_ID
 * //USER_ZDOTDIR=/home/yilin
 * @note
   if (!at_equal)
	{
		// return (NULL);
		return (ft_strdup(input_line));
	}
*/
char	*get_env_id(char *input_line)
{
	char	*at_equal;

	if (!input_line)
		return (NULL);
	at_equal = ft_strchr(input_line, '=');
	if (!at_equal)
		return (ft_strdup(input_line));
	else if (at_equal - input_line == 0)
		return (NULL);
	return (ft_strndup(input_line, at_equal - input_line));
}

/** GET_ENV_VALUE
env_line:    V  A  R  =  v  a  l  u  e
				0  1  2  3  4  5  6  7  8
				^
			env_line
				^
			equal 0
*/
char	*get_env_value(char *input_line)
{
	char	*at_equal;

	if (!input_line)
		return (NULL);
	at_equal = ft_strchr(input_line, '=');
	if (!at_equal)
		return (NULL);
	else if (at_equal - input_line == 0)
		return (NULL);
	return (ft_strdup(input_line + (at_equal - input_line + 1)));
}

/** ENV_CREATE
 * - Allocate memory for a new environment variable node
 * - Initializes its fields.
 *
 * (1) Allocates memory for a t_env structure.
 * (2) If memory allocation fails,
 * -> Free any allocated memory for id & value -> return NULL.
 * (3) Initializes the new structure node with provided args:
 * - id/ value/ env_line
 * (4) Sets the next pointer to NULL.
 * @return pointer to newly created environment variable structure.
 */
t_env	*env_create(char *env_id, char *env_value, char *env_line)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (free(env_id), free(env_value), NULL);
	new->id = env_id;
	new->value = env_value;
	new->env_line = env_line;
	new->next = NULL;
	return (new);
}

/** ENV_ADD_BACK
 * Add a new node to the end of a linked list of environment variables
 * (1) If the list is empty (i.e., *head is NULL)
 * -> it sets *head to point to the new node
 * (2) If the list is not empty
 * 	-> it traverses to the last node of the list
 * (3) Links the new node to the end of the list
 * -> setting the next pointer of the last node to point to the new node
 * @return SUCCESS (0)
 */
int	env_add_back(t_env **head, t_env *new)
{
	t_env	*current;

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

/** ENV_FREE */
void	env_free(t_env *env)
{
	t_env	*tmp_next;

	while (env)
	{
		tmp_next = env->next;
		if (env->id)
			free(env->id);
		if (env->value)
			free(env->value);
		if (env->env_line)
			free(env->env_line);
		free(env);
		env = tmp_next;
	}
}
