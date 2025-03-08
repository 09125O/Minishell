/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/09 00:27:24 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.OD.shell.h"
#include <ctype.h>

/** ERROR EXIT */
void	error_exit(char *input_line)
{
	ft_putstr_fd(P_NAME, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(input_line, STDERR_FILENO);
	ft_putstr_fd(": Numeric argument required\n", STDERR_FILENO);
}

static int	too_many(t_shell *content)
{
	ft_putstr_fd("mini.OD.shell: exit: too many arguments\n", STDERR_FILENO);
	content->exit_code = 1;
	return (1);
}

/** FT_EXIT (no options)
 * exit [n]
 * (1) If more than 1 argument -> error: too many arguments
 * (2) if 1 argument & is a valid exit code (it should be a number)
 * -> exit with exit code
 * (3) If 1 argument & is invalid -> error_exit()
 * (4) Close and free everything
 * @note
 * //Apply modulo 256 to match Bash behavior!!!
 */
int	ft_exit(t_shell *content, t_arg *args)
{
	long	exit_code;

	exit_code = content->exit_code;
	if (args)
	{
		if (check_exitcode(args->value) || ft_atol_overflow(args->value,
				&exit_code))
		{
			error_exit(args->value);
			exit_code = 2;
		}
		else if (args->next)
			return (too_many(content));
		else
			exit_code = (unsigned char)(exit_code % 256);
	}
	else
	{
		if (g_signal.signal_code > 0)
			exit_code = 128 + (g_signal.signal_code - SIG_OFFSET);
	}
	set_std(content, 1);
	free_all_shell(content);
	exit(exit_code);
}
