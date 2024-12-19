/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 22:46:26 by douzgane          #+#    #+#             */
/*   Updated: 2024/12/17 21:24:55 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include <errno.h>

/*
** env_utils functions
*/
/* env_getter.c */
char	*get_env_var(t_env *env, const char *key);
t_env	*get_env_node(t_env *env, const char *key);
int		env_var_exists(t_env *env, const char *key);

/* env_setter.c */
t_env	*create_env_var(const char *key, const char *value);
int		set_env_var(t_env **env, const char *key, const char *value);

/* env_delete.c */
void	free_env_node(t_env *node);
void	free_env_list(t_env *env);
int		unset_env_var(t_env **env, const char *key);

/*
** str_utils functions
*/
/* str_array.c */
int		str_array_len(char **array);
void	free_str_array(char **array);
char	**dup_str_array(char **array);

/* str_split.c */
char	**split_by_char(char *str, char sep);

/* str_join.c */
char	*str_join_with_sep(char *s1, char *s2, char *sep);
char	*str_join_three(char *s1, char *s2, char *s3);

/*
** error functions
*/
/* error_print.c */
void	print_error(const char *cmd, const char *arg, const char *message);
void	print_syntax_error(const char *token);
void	print_command_error(const char *cmd, const char *error);

/* error_handler.c */
void	handle_cmd_error(t_shell *shell, const char *cmd, int err_code);
void	handle_system_error(t_shell *shell, const char *msg);
int		set_error_code(t_shell *shell, int code);

#endif
