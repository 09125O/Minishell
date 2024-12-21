/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:19:10 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/21 15:18:19 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	exec_command(char *cmd, char **env)
{
	char	**cmd_name;
	char	*path;

	cmd_name = ft_split(cmd, ' ');
	// if (is_builtin(cmd_name[0])) // A rajouter une fois aue les built-ins sont gerer
	// {
	// 	execute_builtin(cmd_name);
	// 	free_dbl_tab(cmd_name);
	// 	return;
	// }
	path = path_finder(cmd_name[0], env);
	if (!path || access(path, F_OK | X_OK) != 0)
	{
		perror("minishell: command not found");
		free_dbl_tab(cmd_name);
		exit(127);
	}
	if (execve(path, cmd_name, env) == -1)
	{
		perror("minishell");
		free_dbl_tab(cmd_name);
		exit(126);
	}
}
