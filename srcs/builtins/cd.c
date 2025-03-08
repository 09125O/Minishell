/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 23:07:13 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <string.h>

/** ERROR CD */
void	error_cd(int err_n, char *pathname)
{
	char	*err_msg;

	err_msg = strerror(err_n);
	if (pathname && ft_strcmp(pathname, "HOME") == 0)
	{
		ft_putstr_fd(P_NAME, STDERR_FILENO);
		ft_putstr_fd(": cd: ", STDERR_FILENO);
		ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putstr_fd(" not set\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(P_NAME, STDERR_FILENO);
		ft_putstr_fd(": cd: ", STDERR_FILENO);
		ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err_msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

/** CD (relative or absolute path)
 * 1. Get the number of arguments passed to 'cd'
 * 2. If more than 1 args -> "error: too many arguments"
 * 3. Get the current working directory and store it in variable,
	if fail-> perror
 * 4. Get the 'HOME' environment variable
 * 5.
 **/
int	ft_cd(t_shell *content, t_arg *args)
{
	int		args_nb;
	char	*cwd;
	t_env	*home;

	args_nb = ft_arg_lstsize(args);
	if (args_nb > 1)
		return (ft_putstr_fd("mini.OD.shell: cd: too many arguments\n",
				STDERR_FILENO), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("mini.OD.shell: cd: error retrieving current directory");
	home = get_env("HOME", content->env);
	if ((!args_nb || !ft_strcmp(args->value, "--")) && home && home->value)
		chdir(home->value);
	else if ((!args_nb || !ft_strcmp(args->value, "--")) && (!home
			|| !home->value))
		return (error_cd(errno, "HOME"), free(cwd), 1);
	else if (chdir(args->value) < 0)
	{
		error_cd(errno, args->value);
		return (free(cwd), 1);
	}
	if (update_pwd(content, cwd))
		return (free(cwd), 1);
	return (free(cwd), SUCCESS);
}

/** UPDATE PWD
 * Update PWD + OLDPWD environment variables
 * @param
 * - t_env *old_pwd / pwd: interact wiht the environment
 * - char *current_cwd: Hold raw directory path returned by getcwd()
 * - char *pwd_path
 * - char *oldpwd_path
 * (1) Get the current working directory and store it in new_cwd
 * (2) Retrieve the OLDPWD + PWD env variables frm env list
 * (3) If PWD valid && current_cwd (current working directory) valid,
 * -> Create new string in the format "PWD=<current_working_directory>"
 * -> Check for memory allocation failure OR failure to add variable to env
 * -> Free the temporary string
 * (4) If OLDPWD valid && OLDPWD value exists/provided
 * -> Create a new string "OLDPWD=<previous_working_directory>"
 * -> Check if fail -> Cleanup
 */
int	update_pwd(t_shell *content, char *oldpwd_value)
{
	t_env	*old_pwd;
	t_env	*pwd;
	char	*current_cwd;
	char	*pwd_path;
	char	*oldpwd_path;

	current_cwd = getcwd(NULL, 0);
	old_pwd = get_env("OLDPWD", content->env);
	pwd = get_env("PWD", content->env);
	if (pwd && current_cwd)
	{
		pwd_path = ft_strjoin("PWD=", current_cwd);
		if (!pwd_path || add_envvar(pwd_path, &content->env) != 0)
			return (free(current_cwd), FAILURE);
		free(pwd_path);
	}
	if (old_pwd && oldpwd_value)
	{
		oldpwd_path = ft_strjoin("OLDPWD=", oldpwd_value);
		if (!oldpwd_path || add_envvar(oldpwd_path, &content->env) != 0)
			return (free(current_cwd), FAILURE);
		free(oldpwd_path);
	}
	free(current_cwd);
	return (SUCCESS);
}

/* ft_arg_listsize*/
int	ft_arg_lstsize(t_arg *args)
{
	int	i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}
