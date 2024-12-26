/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouhour <obouhour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:18:29 by obouhour          #+#    #+#             */
/*   Updated: 2024/12/22 12:24:17 by obouhour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*env_srch(char *str, char **env)
{
	char	*check_str;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		j++;
		check_str = ft_substr(env[i], 0, j);
		if (ft_strcmp(check_str, str) == 0)
		{
			free(check_str);
			return (env[i] + j + 1);
		}
		free(check_str);
		i++;
	}
	return (NULL);
}

static char	*check_paths(char **all_path, char *cmd)
{
	char	*path_part;
	char	*command;
	int		i;

	i = 0;
	while (all_path[i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		command = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

char	*path_finder(char *cmd, char **env)
{
	char	**all_path;
	char	*schr_path;
	char	*command;

	schr_path = env_srch("PATH", env); //A voir si on doit ajouter "PATH:" a la place de "PATH"
	if (!schr_path)
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (NULL);
	}
	all_path = ft_split(schr_path, ':');
	if (!all_path)
		return (NULL);
	command = check_paths(all_path, cmd);
	free_dbl_tab(all_path);
	if (command != NULL)
		return (command);
	return (cmd);
}
