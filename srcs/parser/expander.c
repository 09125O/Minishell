/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** PARSE- FT_COUNT_DOLLAR_SIGN
 * Counts how many times the dollar sign ($) appears in a string
 * Determine how many environment variables (envvar) need to be expanded
 */
int	prs_count_dollar_sign(char *input_str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input_str[i])
	{
		if (input_str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

/** PRS_EXPAND_1ENVVAR
 * - Replace SINGLE environment variable(envvar) with corresponding value
 * - Separates the string into parts before and after the environment variable
 * - Retrieves the variable's value from the environment
 * - Lastly joins these parts together with the expanded environment variable
 * @param
 * char *before_envvar; (The part of the string before `$VAR`)
 * char *env_var; (The value of the variable from the environment)
 * char *after_envvar; (The part of the string after `$VAR`)
 * char *new; (The newly constructed string)
 *
 * @note REMEMBER TO FREE USED / INVALID POINTERS!!
 * -> strjoin/append [befor_env & env_var] & [after_env] ;
 * -> free after use or invalid
 * @return String with $VAR replaced with its value.
 */
char	*prs_exapnd_1envvar(char *str, char *envvar_found, t_shell *content)
{
	char	*before_envvar;
	char	*envvar_value;
	char	*after_envvar;
	char	*new;

	before_envvar = get_str_before_envvar(str, envvar_found);
	if (!before_envvar)
		return (NULL);
	envvar_value = get_envvar_value((envvar_found + 1), content);
	after_envvar = get_str_after_envvar(envvar_found);
	if (!after_envvar)
		return (free(before_envvar), free(envvar_value), NULL);
	new = check_null_strjoin(before_envvar, envvar_value);
	if (!new)
		return (free(after_envvar), NULL);
	new = check_null_strjoin(new, after_envvar);
	if (envvar_value)
		free(envvar_value);
	return (free(after_envvar), new);
}

/** PRS_HANDLE ENVVAR EXPANSION
 * - Check how many environment variable(envvar) need expanded
 * - Iterates thru string, expanding ONE environment variable AT A TIME
 * - Expanding environment variables in a SINGLE token
 *
 * -1 Stop char	*prs_exapnd_1envvar() if NO `$` || NO expansions left
 * -2 Stop if Edge cases ie. standalone `$`
	  (environment variable named $ doesn't exist)
 * -3 Store the current value of the token for later freeing
 * -4 Convert the envvar_found environment variable into its value
 * -5 If the expansion results in an empty string
 *    -> clean up + set `new` to NULL
 * -6 Update the token's value with the new string
 * -7 Free used current pointer
*/
int	prs_handle_envvar_expansion(t_token *token)
{
	int		n_dollar;
	char	*current;
	char	*envvar_found;
	char	*new;

	n_dollar = prs_count_dollar_sign(token->value);
	while (token->value != NULL)
	{
		envvar_found = ft_strchr(token->value, '$');
		if (envvar_found == NULL || n_dollar == 0)
			break ;
		if (ft_strcmp(envvar_found, "$") == 0)
			break ;
		current = token->value;
		new = prs_exapnd_1envvar(token->value, envvar_found, token->content);
		if (new && new[0] == '\0')
		{
			free(new);
			new = NULL;
		}
		token->value = new;
		free(current);
		n_dollar--;
	}
	return (SUCCESS);
}
