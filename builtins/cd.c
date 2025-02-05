/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:53:17 by root              #+#    #+#             */
/*   Updated: 2025/02/05 16:12:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_pwd(char **env)
{
	char	*cwd;
	char	*old_pwd;

	old_pwd = ft_getenv("PWD", env); //sera ajouter ensuite avec la partie env
	if (old_pwd)
		ft_setenv("OLDPWD", old_pwd, env); //sera ajouter ensuite avec la partie env
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_setenv("PWD", cwd, env);
		free(cwd);
	}
}

int	ft_cd(char **args, char **env)
{
	char	*path;

	if (!args[1])
	{
		path = init_env("HOME", env); //sera ajouter ensuite avec la partie env
		if (!path)
		{
			ft_error("cd", NULL, "HOME not set");//ft_error sera gerer une fois integrer au reste du code
			return (1);
		}
	}
	else
		path = args[1];

	if (chdir(path) == -1)
	{
		ft_error("cd", path, strerror(errno)); //ft_error sera gerer une fois integrer au reste du code
		return (1);
	}
	update_pwd(env);
	return (0);
}
