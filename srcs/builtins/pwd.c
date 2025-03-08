/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 23:07:23 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/** ERROR PWD */
void	error_pwd(char *option)
{
	ft_putstr_fd(P_NAME, STDERR_FILENO);
	ft_putstr_fd(" pwd: ", STDERR_FILENO);
	ft_putstr_fd(option, STDERR_FILENO);
	ft_putstr_fd(": Invalid option\n", STDERR_FILENO);
}

/** FT_PWD (no options)
 * - pwd -L / pwd -P
 * - If no args
 * -> absolute path name of current directory not containing filenames
 * @param cwd: current working directory
 * @note
 * ***(args->value) == '-'
 * -> to check if the first character is '-' => valid option
 * -> Identify Flag Arguments
 * -> Prevent Invalid Arguments: args->value != "-L" && args->value != "-P"
 * ***Without this check,
	you would attempt to compare a non-flag argument (like L) against "-L",
	which would produce incorrect results.
 */
int	ft_pwd(t_arg *args)
{
	char	*cwd;

	if (args && *(args->value) == '-' && ft_strcmp(args->value, "-L") != 0
		&& ft_strcmp(args->value, "-P") != 0)
	{
		error_pwd(args->value);
		return (FAILURE_VOID);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("mini.OD.shell: pwd: error retrieving current directory");
		return (FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}
