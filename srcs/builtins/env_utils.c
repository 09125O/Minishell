/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/** CHECK_ENVID_VALID
 * (1) Check if env_id empty
 * (2) Check if env_id first character alpha or not '_'
 * (3) Then loop to check if env_id rest of character numeric
 *
 * @note
 * - Valid: "HOME", "USER_NAME", "_PWD".
 * - Invalid: "123ABC", "$PATH", "!VAR" (
 * because the first character is not a letter or underscore)
 *
 */
int	check_envid_valid(char *env_id)
{
	int	i;

	i = 0;
	if (env_id[i] == '\0')
		return (0);
	if (ft_isalpha(env_id[i]) == 0 && env_id[i] != '_')
		return (0);
	i++;
	while (env_id[i])
	{
		if (ft_isalnum(env_id[i]) == 0 && env_id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/** ADD ENVVAR
 * - Adds or updates an environment variable
 * - Ensures that the variable's name and value are valid
 * - Creates a new environment entry or updates an existing one.
 * @param char	*arg_id; (The name/ID of the environment variable)
 * @param char	*arg_value_dup; (Duplicate of the value string)
 * @param t_env	*tmp;
*/
static int	create_add_env(char *env_id, char *input_line,
			char *dup_inputline, t_env **env_head)
{
	char	*env_value;
	t_env	*env;

	env_value = get_env_value(input_line);
	env = env_create(env_id, env_value, dup_inputline);
	if (!env)
	{
		free(input_line);
		if (env_value)
			free(env_value);
		free(env_id);
		return (FAILURE);
	}
	env_add_back(env_head, env);
	return (SUCCESS);
}

int	add_envvar(char *input_line, t_env **env_head)
{
	char	*env_id;
	char	*dup_inputline;
	t_env	*env;

	env_id = get_env_id(input_line);
	env = get_env(env_id, *env_head);
	if (!env_id || !check_envid_valid(env_id))
		return (free(env_id), error_export(input_line), FAILURE);
	dup_inputline = ft_strdup(input_line);
	if (!dup_inputline)
		return (free(env_id), FAILURE);
	if (!env)
	{
		if (create_add_env(env_id, input_line,
				dup_inputline, env_head) == FAILURE)
			return (FAILURE);
	}
	else
	{
		free(env_id);
		update_envvar(env, dup_inputline);
	}
	return (SUCCESS);
}

/** UPDATE_ENV_VAR
 * - Update existing env variable node's value & full line representation
 * - Free old memory for the value and line and assigns new ones
 * (1) Retrieve the value associated with the raw environment string
 * (2) If no valid value found (arg_value == NULL)
 * -> Free the raw string -> exit
 * (3) If the 'node (update_env)' has an existing value 
 * -> Free the old value memory
 * (4) If 'update_env)' has an existing env line (raw string) 
 * -> Free old env_line
 * (5) Assign new value & env_line to the env structure
 */
void	update_envvar(t_env *update_env, char *env_line)
{
	char	*env_value;

	env_value = get_env_value(env_line);
	if (!env_value)
	{
		free(env_value);
		return ;
	}
	if (update_env->value)
		free(update_env->value);
	if (update_env->env_line)
		free(update_env->env_line);
	update_env->value = env_value;
	update_env->env_line = env_line;
}

/* 
////Modified add_envvar////
int	add_envvar(char *input_line, t_env **env_head)
{
	char	*env_id;
	char	*env_value;
	char	*dup_inputline;
	t_env	*env;

	env_id = get_env_id(input_line);
	env = get_env(env_id, *env_head);
	if (!env_id || !check_envid_valid(env_id))
		return (free(env_id), error_export(input_line), FAILURE);
	dup_inputline = ft_strdup(input_line);
	if (!dup_inputline)
		return (free(env_id), FAILURE);
	if (!env)
	{
		env_value = get_env_value(input_line);
		env = env_create(env_id, env_value, dup_inputline);
		if (!env)
		{
			free(input_line);
			if (env_value)
				free(env_value);
			free(env_id);
			env = NULL; //NEEDED in the combined version!
			return (FAILURE);
		}
		env_add_back(env_head, env);
	}
	else
	{
		free(env_id);
		update_envvar(env, dup_inputline);
	}
	return (SUCCESS);
}

////OG add_envvar///
int	add_envvar(char *input_line, t_env **env_head)
{
	env_id = get_env_id(input_line);
	if (!env_id || !check_envid_valid(env_id))
		return (free(env_id), error_export(input_line), FAILURE);
	env_value = get_env_value(input_line);
	if (!env_value)
		return (free(env_id), SUCCESS);
	printf("ENV_ID: %s\n", env_id);
	dup_inputline = ft_strdup(input_line);
	printf("can i come here");
	printf("DUP_INPUTLINE: %s\n", dup_inputline);
	if (!dup_inputline)
		return (free(env_id), FAILURE);
	env = get_env(dup_inputline, *env_head);//input_line
	if (!env)
	{
		env = env_create(env_id, env_value, dup_inputline);//input_line
		if (!env)
			return (free(dup_inputline), free(env_id), FAILURE);//input_line
		env_add_back(env_head, env);
	}
	else
	{
		update_envvar(env, dup_inputline);
		free (env_id);
	}
	// free(dup_inputline);//debug
	return (SUCCESS);
}
*/