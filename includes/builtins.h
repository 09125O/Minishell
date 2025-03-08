/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:46:01 by douzgane          #+#    #+#             */
/*   Updated: 2025/03/08 23:06:56 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../includes/mini.OD.shell.h"

# define P_NAME "mini.OD.shell"

typedef struct s_shell		t_shell;
typedef struct s_env		t_env;
typedef enum e_token_type	t_token_type;
typedef struct s_token		t_token;
typedef struct s_arg		t_arg;
typedef struct s_filename	t_filename;

/* Builtins Handler*/
int		check_is_builtin(char *input_cmd);
int		exec_builtin(t_shell *content, char *input_cmd, t_arg *args);

/* Builtins env*/
int		check_envid_valid(char *env_id);
int		add_envvar(char *env_line, t_env **env_head);
void	update_envvar(t_env *update_env, char *env_line);

/** ft_env / ft_pwd */
int		ft_env(t_shell *content, t_arg *args);
int		ft_pwd(t_arg *args);

/* ft_echo*/
int		ft_echo(t_arg *args);
int		check_echo_has_nargs(char *flag);

/* ft_exit*/
int		ft_exit(t_shell *content, t_arg *args);
int		check_exitcode(char	*input_line);

/* ft_cd */
int		ft_cd(t_shell *content, t_arg *args);
int		update_pwd(t_shell *content, char *oldpwd_value);
int		ft_arg_lstsize(t_arg *args);

/* ft_export */
int		ft_export(t_shell *content, t_arg *args);
int		export_print_sorted_env(t_env *env);
char	**sort_env_arrs(char **env_arrs);

/* ft_unset */
int		ft_unset(t_shell *content, t_arg *args);
int		delete_envvar(char *env_value, t_env **env);
void	env_delete_1node(t_env *env);

/** builtins error1,2 */
void	error_env(char *input_line);
void	error_pwd(char	*option);
void	error_exit(char *input_line);
void	error_cd(int err_n, char *pathname);
void	error_export(char *env_line);
void	error_unset(char *input_line);

#endif
