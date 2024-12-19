/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:54:06 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 16:21:36 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	is_executable(char *path)
{
   struct stat	st;

   if (stat(path, &st) == -1)
   	return (0);
   if (S_ISDIR(st.st_mode))
   	return (0);
   if (access(path, X_OK) == -1)
   	return (0);
   return (1);
}

static char	*get_absolute_path(char *cmd)
{
   char	*path;

   if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
   {
   	if (!is_executable(cmd))
   		return (NULL);
   	path = ft_strdup(cmd);
   	return (path);
   }
   return (NULL);
}

char	**get_path_dirs(char **env)
{
   char	*path_var;
   int		i;

   i = 0;
   while (env[i])
   {
   	if (ft_strncmp(env[i], "PATH=", 5) == 0)
   	{
   		path_var = env[i] + 5;
   		return (split_by_char(path_var, ':'));
   	}
   	i++;
   }
   return (NULL);
}

static char	*try_path_dirs(char *cmd, char **dirs)
{
   char	*path;
   char	*tmp;
   int		i;

   i = 0;
   while (dirs && dirs[i])
   {
   	tmp = ft_strjoin(dirs[i], "/");
   	if (!tmp)
   		return (NULL);
   	path = ft_strjoin(tmp, cmd);
   	free(tmp);
   	if (!path)
   		return (NULL);
   	if (is_executable(path))
   		return (path);
   	free(path);
   	i++;
   }
   return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
   char	*path;
   char	**path_dirs;

   if (!cmd || !env)
   	return (NULL);
   path = get_absolute_path(cmd);
   if (path)
   	return (path);
   path_dirs = get_path_dirs(env);
   if (!path_dirs)
   	return (NULL);
   path = try_path_dirs(cmd, path_dirs);
   free_str_array(path_dirs);
   return (path);
}
