/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** GET_ENV
 * Search for an environment variable by its name (path),
 * in a linked list of environment variables (env)
 */
t_env	*get_env(char *env_id, t_env *env)
{
	if (env_id == NULL || env == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (ft_strcmp(env_id, env->id) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/** PRS_TOKENS_COMBINE
 * (1) Duplicate an empty string ("")
 * -> Initialize `value` as an empty string -> start concatenation process
 * (2) Loop thru token list
 * - If the current token has a non-NULL value -> concatenate it,
 * - Append the token's value to `value` using check_null_strjoin()
 *
 */
char	*prs_tokens_combine(t_token *token)
{
	char	*result;

	result = ft_strdup("");
	while (token != NULL)
	{
		if (token->value != NULL)
		{
			result = check_null_strjoin(result, token->value);
			if (!result)
				break ;
		}
		token = token->next;
	}
	return (result);
}

/** CHECK_NULL_STRJOIN*/
char	*check_null_strjoin(char *s1, char *s2)
{
	char	*result;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s2 == NULL)
		return (s1);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}
