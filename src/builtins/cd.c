/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:15:21 by douzgane          #+#    #+#             */
/*   Updated: 2025/02/25 14:15:21 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "env.h"
#include "shell_ctx.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static int	update_pwd(t_shell_ctx *ctx)
{
	char	*current_pwd;

	if (ctx->cwd)
		env_add(&ctx->env, "OLDPWD", ctx->cwd);
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		ft_error("cd", NULL, strerror(errno));
		return (1);
	}
	env_add(&ctx->env, "PWD", current_pwd);
	if (ctx->old_pwd)
		free(ctx->old_pwd);
	ctx->old_pwd = ctx->cwd;
	ctx->cwd = current_pwd;
	return (0);
}

static char	*expand_home_path(const char *path, t_env *env)
{
	char	*home;

	if (!path || path[0] != '~')
		return (ft_strdup(path));
	home = env_get(env, "HOME");
	if (!home)
		return (NULL);
	if (!path[1])
		return (ft_strdup(home));
	if (path[1] == '/')
		return (ft_strjoin(home, path + 1));
	return (ft_strdup(path));
}

int	ft_cd(char **args, t_shell_ctx *ctx)
{
	char	*path;
	char	*expanded_path;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = env_get(ctx->env, "HOME");
		if (!path)
		{
			ft_error("cd", NULL, "HOME not set");
			return (1);
		}
		expanded_path = ft_strdup(path);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = env_get(ctx->env, "OLDPWD");
		if (!path)
		{
			ft_error("cd", NULL, "OLDPWD not set");
			return (1);
		}
		expanded_path = ft_strdup(path);
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
		expanded_path = expand_home_path(args[1], ctx->env);
	if (!expanded_path)
	{
		ft_error("cd", args[1], "error expanding path");
		return (1);
	}
	if (chdir(expanded_path) == -1)
	{
		ft_error("cd", expanded_path, strerror(errno));
		free(expanded_path);
		return (1);
	}
	free(expanded_path);
	return (update_pwd(ctx));
}
