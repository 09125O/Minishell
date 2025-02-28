/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 15:18:29 by obouhour          #+#    #+#             */
/*   Updated: 2025/02/25 20:24:13 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	*check_path(char *path_part, char *cmd)
{
	char	*command;

	command = ft_strjoin(path_part, "/");
	if (!command)
		return (NULL);
	command = ft_strjoin_free(command, cmd);
	if (!command)
		return (NULL);
	if (access(command, F_OK | X_OK) == 0)
		return (command);
	free(command);
	return (NULL);
}

static char	*find_in_paths(char **paths, char *cmd)
{
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		command = check_path(paths[i], cmd);
		if (command)
			return (command);
		i++;
	}
	return (NULL);
}

char	*path_finder(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_value;
	char	*command;

	if (!cmd || !env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_value = env_get(env, "PATH");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	command = find_in_paths(paths, cmd);
	free_dbl_tab(paths);
	return (command);
}
