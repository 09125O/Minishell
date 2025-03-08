/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

t_signal	g_signal = {0};

/** SET_DEFAULT_ENV
 * Creates a default environment variable node
 * @param def_content:
 * pointer to hold the new environment variable structure
 *
 * (1) Call get_env_id() -> extract env ID
 * (2) Call get_env_value() -> extract env value
 * (3) Call env_create() -> allocate memory for a new t_env structure,
 * (4) Initialize it with extracted env ID/ value/ duplicated string
 * @return def_content
 */
t_env	*set_default_env(void)
{
	char	*env_id;
	char	*env_value;
	t_env	*default_content;

	env_id = get_env_id(DEFAULT_ENV);
	env_value = get_env_value(DEFAULT_ENV);
	default_content = env_create(env_id, env_value, ft_strdup(DEFAULT_ENV));
	return (default_content);
}

/** DUP_ENV
 * Index for iterating through the environment variables
 * env_id: Hold the identifier of the environment variable(before '=')
 * env_value: Hold the value of the environment variable(after '=')
 @note
 * Check if the environment pointer is NULL or points to an empty str
 */
t_env	*dup_env(char *env[])
{
	t_env	*res_env;
	t_env	*tmp;
	char	*env_id;
	char	*env_value;
	int		i;

	i = 0;
	res_env = set_default_env();
	while (env[i])
	{
		env_id = get_env_id(env[i]);
		env_value = get_env_value(env[i]);
		tmp = env_create(env_id, env_value, ft_strdup(env[i]));
		if (!tmp)
			return (NULL);
		env_add_back(&res_env, tmp);
		i++;
	}
	return (res_env);
}

/** INIT_SHELL
* @note
* Alternative way: Can also use memset() to initializing
*/
t_shell	*init_shell(char *env[])
{
	t_shell	*content;

	content = malloc(sizeof(t_shell));
	if (!content)
		return (NULL);
	content->env = dup_env(env);
	if (!(content->env))
	{
		free(content);
		return (NULL);
	}
	content->default_in = STDIN_FILENO;
	content->default_out = STDOUT_FILENO;
	content->pids = NULL;
	content->exec = NULL;
	content->pid_count = 0;
	content->exec_count = 0;
	content->exit_code = 0;
	return (content);
}

/** PROCESS_INPUT
 * Input → Lexing → Parsing → Execution Setup → Execution → Cleanup
 * STEP 1: LEXING:
 * Convert the input string 'line' into tokens (words, operators, etc.)
 * STEP 2: PARSING:
 * Check if tokenized input has correct syntax → prepare it for execution
 * STEP 3: EXECUTION SETUP:
 * Prepare the tokens for execution
 * STEP 4: EXECUTION
 * STEP 5: CLEANUP
 */
int	process_input(t_shell *content, char *line)
{
	t_token	*token;
	int		pars;

	token = lexing(content, line);
	free(line);
	if (!token)
		return (SUCCESS);
	pars = parsing(&token);
	if (pars)
	{
		token_free(token);
		if (pars == FAILURE_VOID)
			return (SUCCESS);
		return (FAILURE);
	}
	if (init_exec(content, &token) != 0)
		return (FAILURE);
	exec(content);
	free_after_process(content, token);
	return (SUCCESS);
}

/** INIT EXEC */
int	init_exec(t_shell *content, t_token **token)
{
	content->exec = build_to_exec(*token);
	token_free(*token);
	*token = NULL;
	if (!content->exec)
		return (FAILURE);
	content->exec_count = ft_build_lstsize(content->exec);
	content->pids = malloc(sizeof(pid_t) * (content->exec_count + 1));
	if (!content->pids)
		return (FAILURE);
	content->pid_count = 0;
	return (SUCCESS);
}
