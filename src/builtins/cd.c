/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:22:54 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 17:02:31 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static char	*get_home_dir(t_shell *shell)
{
   char	*home;

   home = get_env_var(shell->env, "HOME");
   if (home == NULL)
   {
   	print_error("cd", NULL, "HOME not set");
   	return (NULL);
   }
   return (home);
}

static int	update_pwd_vars(t_shell *shell)
{
   char	*pwd;
   char	*old_pwd;

   old_pwd = shell->pwd;
   pwd = getcwd(NULL, 0);
   if (pwd == NULL)
   {
   	print_error("cd", NULL, "getcwd failed");
   	return (EXIT_FAILURE);
   }
   if (old_pwd != NULL)
   	set_env_var(&shell->env, "OLDPWD", old_pwd);
   set_env_var(&shell->env, "PWD", pwd);
   free(shell->pwd);
   shell->pwd = pwd;
   return (EXIT_SUCCESS);
}

static int	change_to_path(t_shell *shell, char *path)
{
   if (chdir(path) == ERROR)
   {
   	print_error("cd", path, strerror(errno));
   	return (EXIT_FAILURE);
   }
   return (update_pwd_vars(shell));
}

static char	*get_target_path(t_shell *shell, char **args)
{
   if (args[1] == NULL)
   	return (get_home_dir(shell));
   return (args[1]);
}

int	ft_cd(t_shell *shell, char **args)
{
   char	*path;

   path = get_target_path(shell, args);
   if (path == NULL)
   	return (EXIT_FAILURE);
   return (change_to_path(shell, path));
}
