/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 21:43:37 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"

/** HANDLE_QMARK_EXIT_STATUS ($?)
* - If a signal code is present, it takes priority.
* - If NO signal code is present, the normal exit code is used.
* @note
* After return the signal code, it’s reset to 0 to avoid using stale
* signal values for future processes.
* @return (string (ft_itoa(code))); If a process was terminated by a signal
* @return (normal exit code (ft_itoa(ctx->exit_code)));
* If the process not terminated by a signal (g_signals.signal_code == 0)

//TO CHECK: *status_code = 0;? should initialize??
*/
char	*handle_qmark_exit_status(t_shell *content)
{
	int	status_code;

	if (g_signal.signal_code != 0)
	{
		status_code = g_signal.signal_code;
		g_signal.signal_code = 0;
		return (ft_itoa(status_code));
	}
	return (ft_itoa(content->exit_code));
}

/** HANDLE DOLLAR SIGN PID ($$)
 * @note Alternative way: return (ft_strdup("program_pid"));
 * Using a constant string instead of actual PID for consistent behavior
 */
char	*handle_dollar_pid(void)
{
	int	pid;

	pid = getpid();
	return (ft_itoa(pid));
}

/** PRS_EXPAND_ENV
 * Iterates through all tokens in a list and applies ps_handle_env()
 * -> Process $VAR expansions
 * Loops through a list of tokens
 * -> Expands environment variables in tokens of type STR or DOUBLEQUOTE
 * It calls ps_handle_env() -> handle the expansion for each token
 * @return Tokens updated with $VAR expansions
 */
int	prs_expand_env(t_token *token)
{
	while (token)
	{
		if (token->type == STR || token->type == DBL_QUOTE)
			prs_handle_envvar_expansion(token);
		token = token->next;
	}
	return (SUCCESS);
}
