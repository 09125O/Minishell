/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:53:17 by root              #+#    #+#             */
/*   Updated: 2025/02/10 13:09:13 by root             ###   ########.fr       */
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

int	ft_cd(char **args, t_env *env)
{
	char	*path;

	if (!args || !env)
		return (1);
	if (!args[1])
	{
		path = search_env_variable(env, "HOME");  // Utiliser search_env_variable au lieu de init_env
		if (!path)
		{
			ft_error("cd", NULL, "HOME not set");
			return (1);
		}
	}
	else if (args[1][0] == '-' && !args[1][1])
	{
		path = search_env_variable(env, "OLDPWD"); // Ajouter support pour 'cd -'
		if (!path)
		{
			ft_error("cd", NULL, "OLDPWD not set");
			return (1);
		}
		printf("%s\n", path);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		ft_error("cd", path, strerror(errno));
		return (1);
	}
	update_pwd(env->vars);  // Passer env->vars à update_pwd
	return (0);
}
